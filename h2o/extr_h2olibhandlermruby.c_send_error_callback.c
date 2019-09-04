#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_8__ {int /*<<< orphan*/  exc; } ;
typedef  TYPE_2__ mrb_state ;
typedef  int /*<<< orphan*/  h2o_mruby_generator_t ;
struct TYPE_9__ {TYPE_1__* shared; } ;
typedef  TYPE_3__ h2o_mruby_context_t ;
struct TYPE_7__ {TYPE_2__* mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/ * h2o_mruby_get_generator (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_exception (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_ptr (int /*<<< orphan*/ ) ; 

mrb_value send_error_callback(h2o_mruby_context_t *ctx, mrb_value input, mrb_value *receiver, mrb_value args, int *run_again)
{
    mrb_state *mrb = ctx->shared->mrb;
    mrb->exc = mrb_obj_ptr(mrb_ary_entry(args, 0));
    h2o_mruby_generator_t *generator = h2o_mruby_get_generator(mrb, mrb_ary_entry(args, 1));
    handle_exception(ctx, generator);
    return mrb_nil_value();
}