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
struct TYPE_3__ {int /*<<< orphan*/ * mrb; } ;
typedef  TYPE_1__ h2o_mruby_shared_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_CODE_REDIS ; 
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  call_method ; 
 int /*<<< orphan*/  connect_method ; 
 int /*<<< orphan*/  disconnect_method ; 
 int /*<<< orphan*/  disconnected_method ; 
 int /*<<< orphan*/  h2o_mruby_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_define_callback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_eval_expr_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 int /*<<< orphan*/  mrb_define_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  redis_join_reply_callback ; 
 int /*<<< orphan*/  setup_method ; 

void h2o_mruby_redis_init_context(h2o_mruby_shared_context_t *ctx)
{
    mrb_state *mrb = ctx->mrb;

    h2o_mruby_eval_expr_location(mrb, H2O_MRUBY_CODE_REDIS, "(h2o)lib/handler/mruby/embedded/redis.rb", 1);
    h2o_mruby_assert(mrb);

    struct RClass *module = mrb_define_module(mrb, "H2O");

    h2o_mruby_define_callback(mrb, "_h2o__redis_join_reply", redis_join_reply_callback);

    struct RClass *redis_klass = mrb_class_get_under(mrb, module, "Redis");
    mrb_define_method(mrb, redis_klass, "__setup", setup_method, MRB_ARGS_NONE());
    mrb_define_method(mrb, redis_klass, "__connect", connect_method, MRB_ARGS_NONE());
    mrb_define_method(mrb, redis_klass, "disconnected?", disconnected_method, MRB_ARGS_NONE());
    mrb_define_method(mrb, redis_klass, "disconnect", disconnect_method, MRB_ARGS_NONE());
    mrb_define_method(mrb, redis_klass, "__call", call_method, MRB_ARGS_ARG(1, 0));
}