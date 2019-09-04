#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {int /*<<< orphan*/  blocking_reqs; int /*<<< orphan*/  proc; TYPE_1__* shared; } ;
typedef  TYPE_2__ h2o_mruby_context_t ;
struct TYPE_4__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

mrb_value block_request_callback(h2o_mruby_context_t *ctx, mrb_value input, mrb_value *receiver, mrb_value args, int *run_again)
{
    mrb_state *mrb = ctx->shared->mrb;
    mrb_value blocking_req = mrb_ary_new_capa(mrb, 2);
    mrb_ary_set(mrb, blocking_req, 0, ctx->proc);
    mrb_ary_set(mrb, blocking_req, 1, input);
    mrb_ary_push(mrb, ctx->blocking_reqs, blocking_req);
    return mrb_nil_value();
}