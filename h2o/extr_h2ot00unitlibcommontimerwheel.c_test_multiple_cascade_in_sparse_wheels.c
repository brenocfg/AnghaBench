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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  h2o_timerwheel_t ;
typedef  int /*<<< orphan*/  h2o_timerwheel_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * h2o_timerwheel_create (int,int const) ; 
 int /*<<< orphan*/  h2o_timerwheel_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timerwheel_init_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timerwheel_link_abs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  h2o_timerwheel_run (int /*<<< orphan*/ *,int const) ; 
 int invokes ; 
 int /*<<< orphan*/  my_callback ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_multiple_cascade_in_sparse_wheels(void)
{
    const uint64_t base_time = 0x1659418c000;
    h2o_timerwheel_t *ctx = h2o_timerwheel_create(3, base_time - 2048);
    h2o_timerwheel_entry_t t1, t2;

    invokes = 0;

    h2o_timerwheel_init_entry(&t1, my_callback);
    h2o_timerwheel_link_abs(ctx, &t1, base_time);

    h2o_timerwheel_run(ctx, base_time - 100);
    ok(invokes == 0);

    h2o_timerwheel_init_entry(&t2, my_callback);
    h2o_timerwheel_link_abs(ctx, &t2, base_time);

    h2o_timerwheel_run(ctx, base_time - 100);
    ok(invokes == 0);

    h2o_timerwheel_run(ctx, base_time);
    ok(invokes == 2);

    h2o_timerwheel_run(ctx, base_time + 1024);

    h2o_timerwheel_destroy(ctx);
}