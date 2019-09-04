#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ has_content; } ;
struct st_h2o_mruby_http_request_context_t {int consumed; TYPE_1__ resp; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {TYPE_2__* shared; } ;
typedef  TYPE_3__ h2o_mruby_context_t ;
struct TYPE_6__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  attach_receiver (struct st_h2o_mruby_http_request_context_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_chunk (struct st_h2o_mruby_http_request_context_t*) ; 
 int /*<<< orphan*/  create_already_consumed_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_stream_type ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mrb_bool (int /*<<< orphan*/ ) ; 
 struct st_h2o_mruby_http_request_context_t* mrb_data_check_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_exc_new_str_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value http_fetch_chunk_callback(h2o_mruby_context_t *mctx, mrb_value input, mrb_value *receiver, mrb_value args,
                                           int *run_again)
{
    mrb_state *mrb = mctx->shared->mrb;
    struct st_h2o_mruby_http_request_context_t *ctx;
    mrb_value ret;

    if ((ctx = mrb_data_check_get_ptr(mrb, mrb_ary_entry(args, 0), &input_stream_type)) == NULL) {
        *run_again = 1;
        return mrb_exc_new_str_lit(mrb, E_ARGUMENT_ERROR, "_HttpInputStream#each wrong self");
    }

    mrb_value first = mrb_ary_entry(args, 1);
    if (mrb_bool(first)) {
        /* check the body hasn't already consumed */
        if (ctx->consumed) {
            *run_again = 1;
            return create_already_consumed_error(mrb);
        }
        ctx->consumed = 1;
    }

    if (ctx->resp.has_content) {
        ret = build_chunk(ctx);
        *run_again = 1;
    } else {
        attach_receiver(ctx, *receiver);
        ret = mrb_nil_value();
    }

    return ret;
}