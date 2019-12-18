#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {int /*<<< orphan*/  constants; int /*<<< orphan*/ * mrb; } ;
typedef  TYPE_1__ h2o_mruby_shared_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_CHANNEL_CLASS ; 
 int /*<<< orphan*/  H2O_MRUBY_CODE_CHANNEL ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  channel_initialize_method ; 
 int /*<<< orphan*/  channel_notify_method ; 
 int /*<<< orphan*/  h2o_mruby_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_define_callback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_eval_expr_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 int /*<<< orphan*/  mrb_define_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  wait_callback ; 

void h2o_mruby_channel_init_context(h2o_mruby_shared_context_t *shared_ctx)
{
    mrb_state *mrb = shared_ctx->mrb;

    h2o_mruby_eval_expr_location(mrb, H2O_MRUBY_CODE_CHANNEL, "(h2o)lib/handler/mruby/embedded/channel.rb", 1);
    h2o_mruby_assert(mrb);

    struct RClass *module, *klass;
    module = mrb_define_module(mrb, "H2O");

    klass = mrb_class_get_under(mrb, module, "Channel");
    MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);
    mrb_ary_set(mrb, shared_ctx->constants, H2O_MRUBY_CHANNEL_CLASS, mrb_obj_value(klass));
    mrb_define_method(mrb, klass, "initialize", channel_initialize_method, MRB_ARGS_NONE());
    mrb_define_method(mrb, klass, "_notify", channel_notify_method, MRB_ARGS_NONE());
    h2o_mruby_define_callback(mrb, "_h2o__channel_wait", wait_callback);
}