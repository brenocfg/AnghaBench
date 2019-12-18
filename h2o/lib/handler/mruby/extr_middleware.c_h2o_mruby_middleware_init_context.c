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
 int /*<<< orphan*/  H2O_MRUBY_APP_INPUT_STREAM_CLASS ; 
 int /*<<< orphan*/  H2O_MRUBY_APP_REQUEST_CLASS ; 
 int /*<<< orphan*/  H2O_MRUBY_CODE_MIDDLEWARE ; 
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  build_response_method ; 
 int /*<<< orphan*/  can_build_response_method ; 
 int /*<<< orphan*/  h2o_mruby_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_define_callback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_eval_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  middleware_request_method ; 
 int /*<<< orphan*/  middleware_wait_chunk_callback ; 
 int /*<<< orphan*/  middleware_wait_response_callback ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 int /*<<< orphan*/  mrb_define_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 

void h2o_mruby_middleware_init_context(h2o_mruby_shared_context_t *shared_ctx)
{
    mrb_state *mrb = shared_ctx->mrb;

    h2o_mruby_eval_expr(mrb, H2O_MRUBY_CODE_MIDDLEWARE);
    h2o_mruby_assert(mrb);

    struct RClass *module = mrb_define_module(mrb, "H2O");

    struct RClass *app_klass = mrb_class_get_under(shared_ctx->mrb, module, "App");
    mrb_define_method(mrb, app_klass, "request", middleware_request_method, MRB_ARGS_ARG(1, 0));

    struct RClass *app_request_klass = mrb_class_get_under(shared_ctx->mrb, module, "AppRequest");
    mrb_ary_set(shared_ctx->mrb, shared_ctx->constants, H2O_MRUBY_APP_REQUEST_CLASS, mrb_obj_value(app_request_klass));
    h2o_mruby_define_callback(mrb, "_h2o_middleware_wait_response", middleware_wait_response_callback);
    mrb_define_method(mrb, app_request_klass, "_can_build_response?", can_build_response_method, MRB_ARGS_NONE());
    mrb_define_method(mrb, app_request_klass, "_build_response", build_response_method, MRB_ARGS_NONE());

    struct RClass *app_input_stream_klass = mrb_class_get_under(shared_ctx->mrb, module, "AppInputStream");
    mrb_ary_set(shared_ctx->mrb, shared_ctx->constants, H2O_MRUBY_APP_INPUT_STREAM_CLASS, mrb_obj_value(app_input_stream_klass));
    h2o_mruby_define_callback(mrb, "_h2o_middleware_wait_chunk", middleware_wait_chunk_callback);

    h2o_mruby_assert(mrb);
}