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
 int invokes ; 
 int lcg_rand () ; 
 int /*<<< orphan*/  my_callback ; 
 int /*<<< orphan*/  ok (int) ; 

void test_add_rand_timers()
{
    uint32_t abs_wtime = 3;
    h2o_timerwheel_t *testwheel = h2o_timerwheel_create(6, abs_wtime);
    h2o_timerwheel_entry_t timers[N];
    int i;

    /* add timers */
    for (i = 0; i < N; i++) {
        uint32_t expiry = abs_wtime + lcg_rand() % N;
        h2o_timerwheel_init_entry(&timers[i], my_callback);
        h2o_timerwheel_link_abs(testwheel, &timers[i], expiry);
    }

    int start = invokes;
    /* run the wheel: the timers has a max expiry N-1 + abs_wtime  */
    ok(h2o_timerwheel_run(testwheel, N - 1 + abs_wtime) == N);
    ok(invokes - start == N);
    DUMP_WHEEL(testwheel);

    h2o_timerwheel_destroy(testwheel);
}