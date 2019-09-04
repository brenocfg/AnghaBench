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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  h2o_timerwheel_t ;
typedef  int /*<<< orphan*/  h2o_timerwheel_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_WHEEL (int /*<<< orphan*/ *) ; 
 int N ; 
 int /*<<< orphan*/ * h2o_timerwheel_create (int,int) ; 
 int /*<<< orphan*/  h2o_timerwheel_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timerwheel_init_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timerwheel_link_abs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int h2o_timerwheel_run (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_timerwheel_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  my_callback ; 
 int /*<<< orphan*/  ok (int) ; 

void test_del_timers()
{
    uint32_t abs_wtime = 3;
    h2o_timerwheel_t *testwheel = h2o_timerwheel_create(6, abs_wtime);
    h2o_timerwheel_entry_t timers[N];
    int i;

    /* add N timers */
    for (i = 0; i < N; i++) {
        uint32_t expiry = abs_wtime + i + 5;
        h2o_timerwheel_init_entry(&timers[i], my_callback);
        h2o_timerwheel_link_abs(testwheel, &timers[i], expiry);
    }

    /* delete N-1 timers, so there should be 1 timer left */
    for (i = 0; i < N - 1; i++) {
        h2o_timerwheel_unlink(&timers[i]);
    }

    /* run the wheel */
    ok(h2o_timerwheel_run(testwheel, N + 6) == 0);
    DUMP_WHEEL(testwheel);
    ok(h2o_timerwheel_run(testwheel, N + 7) == 1);
    DUMP_WHEEL(testwheel);

    h2o_timerwheel_destroy(testwheel);
}