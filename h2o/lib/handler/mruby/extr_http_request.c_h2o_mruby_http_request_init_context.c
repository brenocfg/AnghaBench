#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  kernel_module; } ;
typedef  TYPE_1__ mrb_state ;
struct TYPE_12__ {int /*<<< orphan*/  constants; TYPE_1__* mrb; } ;
typedef  TYPE_2__ h2o_mruby_shared_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_CODE_HTTP_REQUEST ; 
 int /*<<< orphan*/  H2O_MRUBY_HTTP_EMPTY_INPUT_STREAM_CLASS ; 
 int /*<<< orphan*/  H2O_MRUBY_HTTP_INPUT_STREAM_CLASS ; 
 int /*<<< orphan*/  H2O_MRUBY_HTTP_REQUEST_CLASS ; 
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int) ; 
 int /*<<< orphan*/  h2o_mruby_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_mruby_define_callback (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_eval_expr_location (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  http_fetch_chunk_callback ; 
 int /*<<< orphan*/  http_join_response_callback ; 
 int /*<<< orphan*/  http_request_method ; 
 int /*<<< orphan*/  mrb_ary_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_get_under (TYPE_1__*,struct RClass*,char*) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 

void h2o_mruby_http_request_init_context(h2o_mruby_shared_context_t *ctx)
{
    mrb_state *mrb = ctx->mrb;

    h2o_mruby_eval_expr_location(mrb, H2O_MRUBY_CODE_HTTP_REQUEST, "(h2o)lib/handler/mruby/embedded/http_request.rb", 1);
    h2o_mruby_assert(mrb);

    struct RClass *module, *klass;
    module = mrb_define_module(mrb, "H2O");

    mrb_define_method(mrb, mrb->kernel_module, "http_request", http_request_method, MRB_ARGS_ARG(1, 2));

    klass = mrb_class_get_under(mrb, module, "HttpRequest");
    mrb_ary_set(mrb, ctx->constants, H2O_MRUBY_HTTP_REQUEST_CLASS, mrb_obj_value(klass));

    klass = mrb_class_get_under(mrb, module, "HttpInputStream");
    mrb_ary_set(mrb, ctx->constants, H2O_MRUBY_HTTP_INPUT_STREAM_CLASS, mrb_obj_value(klass));

    klass = mrb_class_get_under(mrb, klass, "Empty");
    mrb_ary_set(mrb, ctx->constants, H2O_MRUBY_HTTP_EMPTY_INPUT_STREAM_CLASS, mrb_obj_value(klass));

    h2o_mruby_define_callback(mrb, "_h2o__http_join_response", http_join_response_callback);
    h2o_mruby_define_callback(mrb, "_h2o__http_fetch_chunk", http_fetch_chunk_callback);
}