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
typedef  scalar_t__ uint64_t ;
struct theft {int dummy; } ;
struct test_timer {int called; int /*<<< orphan*/  t; } ;
struct test_input {scalar_t__ init_time; scalar_t__ first_time; int second_time; } ;
typedef  int /*<<< orphan*/  h2o_timerwheel_t ;
typedef  enum theft_trial_res { ____Placeholder_theft_trial_res } theft_trial_res ;

/* Variables and functions */
 int THEFT_TRIAL_FAIL ; 
 int THEFT_TRIAL_PASS ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/ * h2o_timerwheel_create (int,scalar_t__) ; 
 int /*<<< orphan*/  h2o_timerwheel_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_timerwheel_get_wake_at (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timerwheel_init_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timerwheel_link_abs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 size_t h2o_timerwheel_run (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ theft_random_choice (struct theft*,size_t) ; 
 int /*<<< orphan*/  timer_cb ; 

__attribute__((used)) static enum theft_trial_res prop_inserted_timer_should_not_run_before_reaching_expiry(struct theft *theft, void *input_)
{
    struct test_input *input = input_;
    uint64_t i;
    size_t events_run;
    h2o_timerwheel_t *ctx;
    ctx = h2o_timerwheel_create(6, input->init_time);
    h2o_timerwheel_run(ctx, input->init_time);
    size_t slices = 1;

    struct test_timer t;
    h2o_timerwheel_init_entry(&t.t, timer_cb);
    t.called = 0;
    h2o_timerwheel_link_abs(ctx, &t.t, input->first_time);

    slices = input->second_time / 100;
    for (i = input->init_time; i < input->first_time; i += theft_random_choice(theft, slices)) {
        events_run = h2o_timerwheel_run(ctx, i);
        if (events_run != 0)
            return THEFT_TRIAL_FAIL;
        if (t.called != 0)
            return THEFT_TRIAL_FAIL;
        if (h2o_timerwheel_get_wake_at(ctx) == UINT64_MAX)
            return THEFT_TRIAL_FAIL;
    }

    events_run = h2o_timerwheel_run(ctx, i);

    if (events_run != 1)
        return THEFT_TRIAL_FAIL;
    if (t.called != 1)
        return THEFT_TRIAL_FAIL;
    if (h2o_timerwheel_get_wake_at(ctx) != UINT64_MAX)
        return THEFT_TRIAL_FAIL;
    h2o_timerwheel_destroy(ctx);
    return THEFT_TRIAL_PASS;
}