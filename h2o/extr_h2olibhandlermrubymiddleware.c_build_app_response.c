#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_10__ {scalar_t__ status; scalar_t__ content_length; TYPE_7__ headers; } ;
struct TYPE_12__ {TYPE_2__ res; int /*<<< orphan*/  pool; } ;
struct st_mruby_subreq_t {TYPE_5__* ctx; TYPE_4__ super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_11__ {TYPE_1__ buf; } ;
typedef  TYPE_3__ h2o_token_t ;
typedef  TYPE_4__ h2o_req_t ;
struct TYPE_13__ {TYPE_6__* shared; } ;
typedef  TYPE_5__ h2o_mruby_context_t ;
struct TYPE_14__ {int /*<<< orphan*/  constants; int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_APP_INPUT_STREAM_CLASS ; 
 TYPE_3__* H2O_TOKEN_CONTENT_LENGTH ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  app_input_stream_type ; 
 int /*<<< orphan*/  h2o_mruby_create_data_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct st_mruby_subreq_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_iterate_native_headers (TYPE_6__*,int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_new_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterate_headers_callback ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value build_app_response(struct st_mruby_subreq_t *subreq)
{
    h2o_req_t *req = &subreq->super;
    h2o_mruby_context_t *ctx = subreq->ctx;
    mrb_state *mrb = ctx->shared->mrb;

    /* build response array */
    mrb_value resp = mrb_ary_new_capa(mrb, 3);

    /* status */
    mrb_ary_set(mrb, resp, 0, mrb_fixnum_value(req->res.status));

    /* headers */
    {
        mrb_value headers_hash = mrb_hash_new_capa(mrb, (int)req->res.headers.size);
        h2o_mruby_iterate_native_headers(ctx->shared, &req->pool, &req->res.headers, iterate_headers_callback,
                                         mrb_obj_ptr(headers_hash));
        if (req->res.content_length != SIZE_MAX) {
            h2o_token_t *token = H2O_TOKEN_CONTENT_LENGTH;
            mrb_value n = h2o_mruby_new_str(mrb, token->buf.base, token->buf.len);
            mrb_value v = h2o_mruby_to_str(mrb, mrb_fixnum_value(req->res.content_length));
            mrb_hash_set(mrb, headers_hash, n, v);
        }
        mrb_ary_set(mrb, resp, 1, headers_hash);
    }

    /* body */
    {
        mrb_value body = h2o_mruby_create_data_instance(
            mrb, mrb_ary_entry(ctx->shared->constants, H2O_MRUBY_APP_INPUT_STREAM_CLASS), subreq, &app_input_stream_type);
        mrb_funcall(mrb, body, "initialize", 0);
        mrb_ary_set(mrb, resp, 2, body);
    }

    return resp;
}