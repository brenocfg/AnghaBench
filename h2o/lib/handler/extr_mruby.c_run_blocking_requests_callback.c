#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_9__ {int /*<<< orphan*/  exc; } ;
typedef  TYPE_2__ mrb_state ;
typedef  scalar_t__ mrb_int ;
struct TYPE_10__ {int /*<<< orphan*/  blocking_reqs; TYPE_1__* shared; } ;
typedef  TYPE_3__ h2o_mruby_context_t ;
struct TYPE_8__ {TYPE_2__* mrb; } ;

/* Variables and functions */
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_run_fiber (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_exception (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_ptr (int /*<<< orphan*/ ) ; 

mrb_value run_blocking_requests_callback(h2o_mruby_context_t *ctx, mrb_value input, mrb_value *receiver, mrb_value args,
                                         int *run_again)
{
    mrb_state *mrb = ctx->shared->mrb;

    mrb_value exc = mrb_ary_entry(args, 0);
    if (!mrb_nil_p(exc)) {
        mrb->exc = mrb_obj_ptr(exc);
        handle_exception(ctx, NULL);
    }

    mrb_int i;
    mrb_int len = RARRAY_LEN(ctx->blocking_reqs);
    for (i = 0; i != len; ++i) {
        mrb_value blocking_req = mrb_ary_entry(ctx->blocking_reqs, i);
        mrb_value blocking_req_resumer = mrb_ary_entry(blocking_req, 0);
        mrb_value blocking_req_input = mrb_ary_entry(blocking_req, 1);
        h2o_mruby_run_fiber(ctx, blocking_req_resumer, blocking_req_input, NULL);
    }
    mrb_ary_clear(mrb, ctx->blocking_reqs);

    return mrb_nil_value();
}