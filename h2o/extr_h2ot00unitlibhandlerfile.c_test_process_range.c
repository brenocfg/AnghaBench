#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int) ; 
 size_t* process_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t*) ; 

__attribute__((used)) static void test_process_range(void)
{
    h2o_mem_pool_t testpool;
    size_t ret, *ranges;
    h2o_iovec_t testrange;
    h2o_mem_init_pool(&testpool);

    { /* check single range within filesize */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=, 0-10"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 1);
        ok(*ranges++ == 0);
        ok(*ranges == 11);
    }

    { /* check single range with only start */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=60-"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 1);
        ok(*ranges++ == 60);
        ok(*ranges == 40);
    }

    { /* check single suffix range */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=-10"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 1);
        ok(*ranges++ == 90);
        ok(*ranges == 10);
    }

    { /* this and next two check multiple ranges within filesize */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=0-10, -10"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 2);
        ok(*ranges++ == 0);
        ok(*ranges++ == 11);
        ok(*ranges++ == 90);
        ok(*ranges == 10);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=0-0, 20-89"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 2);
        ok(*ranges++ == 0);
        ok(*ranges++ == 1);
        ok(*ranges++ == 20);
        ok(*ranges == 70);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=-10,-20"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 2);
        ok(*ranges++ == 90);
        ok(*ranges++ == 10);
        ok(*ranges++ == 80);
        ok(*ranges++ == 20);
    }

    { /* check ranges entirely out of filesize */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=100-102"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    { /* check ranges with "negative" length */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=70-21"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    { /* check ranges with one side inside filesize */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=90-102"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 1);
        ok(*ranges++ == 90);
        ok(*ranges == 10);
    }

    { /* check suffix range larger than filesize */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=-200"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 1);
        ok(*ranges++ == 0);
        ok(*ranges == 100);
    }

    { /* check multiple ranges with unsatisfiable ranges, but also contain satisfiable ranges */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=100-102,  90-102, 72-30,-22, 95-"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 3);
        ok(*ranges++ == 90);
        ok(*ranges++ == 10);
        ok(*ranges++ == 78);
        ok(*ranges++ == 22);
        ok(*ranges++ == 95);
        ok(*ranges++ == 5);
    }

    { /* this and next 6 check malformed ranges */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes 20-1002"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes="));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bsdfeadsfjwleakjf"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=100-102, 90-102, -72-30,-22,95-"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=10-12-13, 90-102, -72, -22, 95-"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=100-102, 90-102, 70-39, -22$"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=-0"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    { /* check same ranges with different filesize */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=20-200"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 1);
        ok(*ranges++ == 20);
        ok(*ranges == 80);
    }

    {
        ranges = process_range(&testpool, &testrange, 1000, &ret);
        ok(ret == 1);
        ok(*ranges++ == 20);
        ok(*ranges == 181);
    }

    { /* check a range with plenty of WS and COMMA */
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=,\t,1-3 ,, ,5-9,"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 2);
        ok(*ranges++ == 1);
        ok(*ranges++ == 3);
        ok(*ranges++ == 5);
        ok(*ranges == 5);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes= 1-3"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=1-3 5-10"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ranges == NULL);
    }

    {
        testrange = h2o_iovec_init(H2O_STRLIT("bytes=1-\t,5-10"));
        ranges = process_range(&testpool, &testrange, 100, &ret);
        ok(ret == 2);
        ok(*ranges++ == 1);
        ok(*ranges++ == 99);
        ok(*ranges++ == 5);
        ok(*ranges == 6);
    }

    h2o_mem_clear_pool(&testpool);
}