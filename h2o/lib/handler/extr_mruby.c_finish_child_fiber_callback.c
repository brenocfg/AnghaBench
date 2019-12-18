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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  h2o_mruby_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_nil_value () ; 

mrb_value finish_child_fiber_callback(h2o_mruby_context_t *ctx, mrb_value input, mrb_value *receiver, mrb_value args,
                                      int *run_again)
{
    /* do nothing */
    return mrb_nil_value();
}