#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <algorithm>

#include <boost/heap/fibonacci_heap.hpp>

#include "common_heap_tests.hpp"
#include "stable_heap_tests.hpp"
#include "mutable_heap_tests.hpp"
#include "merge_heap_tests.hpp"


template <bool stable, bool constant_time_size>
void run_fibonacci_heap_test(void)
{
    typedef boost::heap::fibonacci_heap<int, boost::heap::stable<stable>,
                                             boost::heap::compare<std::less<int> >,
                                             boost::heap::allocator<std::allocator<int> >,
                                             boost::heap::constant_time_size<constant_time_size>
                                       > pri_queue;

    BOOST_CONCEPT_ASSERT((boost::heap::MutablePriorityQueue<pri_queue>));
    BOOST_CONCEPT_ASSERT((boost::heap::MergablePriorityQueue<pri_queue>));

    run_common_heap_tests<pri_queue>();
    run_iterator_heap_tests<pri_queue>();
    run_copyable_heap_tests<pri_queue>();
    run_moveable_heap_tests<pri_queue>();

    run_merge_tests<pri_queue>();

    run_mutable_heap_tests<pri_queue>();
    run_ordered_iterator_tests<pri_queue>();

    if (stable) {
        typedef boost::heap::fibonacci_heap<q_tester, boost::heap::stable<stable>,
                                            boost::heap::constant_time_size<constant_time_size>
                                           > stable_pri_queue;
        run_stable_heap_tests<stable_pri_queue>();
    }
}

BOOST_AUTO_TEST_CASE( fibonacci_heap_test )
{
    run_fibonacci_heap_test<true, false>();
    run_fibonacci_heap_test<true, true>();

    run_fibonacci_heap_test<false, false>();
    run_fibonacci_heap_test<false, true>();
}
