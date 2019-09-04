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
struct st_h2o_mruby_redis_command_context_t {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {TYPE_1__* shared; } ;
typedef  TYPE_2__ h2o_mruby_context_t ;
struct TYPE_4__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  attach_receiver (struct st_h2o_mruby_redis_command_context_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_type ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct st_h2o_mruby_redis_command_context_t* mrb_data_check_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_exc_new_str_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value redis_join_reply_callback(h2o_mruby_context_t *mctx, mrb_value input, mrb_value *receiver, mrb_value args,
                                           int *run_again)
{
    mrb_state *mrb = mctx->shared->mrb;
    struct st_h2o_mruby_redis_command_context_t *ctx;

    if ((ctx = mrb_data_check_get_ptr(mrb, mrb_ary_entry(args, 0), &command_type)) == NULL)
        return mrb_exc_new_str_lit(mrb, E_ARGUMENT_ERROR, "Redis::Command#join wrong self");

    attach_receiver(ctx, *receiver);
    return mrb_nil_value();
}