#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_21__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;

/* Type definitions */
struct TYPE_27__ {int /*<<< orphan*/  request; int /*<<< orphan*/  input_stream; } ;
struct TYPE_25__ {scalar_t__ method_is_head; } ;
struct st_h2o_mruby_http_request_context_t {TYPE_17__* ctx; TYPE_4__ refs; int /*<<< orphan*/  receiver; TYPE_2__ req; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_28__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_5__ mrb_state ;
struct TYPE_23__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_29__ {TYPE_1__ value; TYPE_21__* name; } ;
typedef  TYPE_6__ h2o_header_t ;
struct TYPE_26__ {int /*<<< orphan*/  constants; TYPE_5__* mrb; } ;
struct TYPE_24__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_22__ {TYPE_3__* shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_HTTP_EMPTY_INPUT_STREAM_CLASS ; 
 int /*<<< orphan*/  H2O_MRUBY_HTTP_INPUT_STREAM_CLASS ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  detach_receiver (struct st_h2o_mruby_http_request_context_t*) ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 scalar_t__ h2o_memis (TYPE_21__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  h2o_mruby_create_data_instance (TYPE_5__*,int /*<<< orphan*/ ,struct st_h2o_mruby_http_request_context_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_new_str (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_new_str_static (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_run_fiber (TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_stream_type ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (TYPE_5__*,int) ; 
 int /*<<< orphan*/  mrb_ary_set (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (TYPE_5__*,int) ; 
 int mrb_gc_arena_save (TYPE_5__*) ; 
 int /*<<< orphan*/  mrb_hash_new_capa (TYPE_5__*,int) ; 
 int /*<<< orphan*/  mrb_hash_set (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void post_response(struct st_h2o_mruby_http_request_context_t *ctx, int status, const h2o_header_t *headers_sorted,
                          size_t num_headers, int header_requires_dup)
{
    mrb_state *mrb = ctx->ctx->shared->mrb;
    int gc_arena = mrb_gc_arena_save(mrb);
    size_t i;

    mrb_value resp = mrb_ary_new_capa(mrb, 3);

    /* set status */
    mrb_ary_set(mrb, resp, 0, mrb_fixnum_value(status));

    /* set headers */
    mrb_value headers_hash = mrb_hash_new_capa(mrb, (int)num_headers);
    for (i = 0; i < num_headers; ++i) {
        /* skip the headers, we determine the eos! */
        if (h2o_memis(headers_sorted[i].name, headers_sorted[i].name->len, H2O_STRLIT("content-length")) ||
            h2o_memis(headers_sorted[i].name, headers_sorted[i].name->len, H2O_STRLIT("transfer-encoding")))
            continue;
        /* build and set the hash entry */
        mrb_value k, v;
        if (header_requires_dup) {
            k = h2o_mruby_new_str(mrb, headers_sorted[i].name->base, headers_sorted[i].name->len);
            v = h2o_mruby_new_str(mrb, headers_sorted[i].value.base, headers_sorted[i].value.len);
        } else {
            k = h2o_mruby_new_str_static(mrb, headers_sorted[i].name->base, headers_sorted[i].name->len);
            v = h2o_mruby_new_str_static(mrb, headers_sorted[i].value.base, headers_sorted[i].value.len);
        }
        while (i + 1 < num_headers && h2o_memis(headers_sorted[i].name->base, headers_sorted[i].name->len,
                                                headers_sorted[i + 1].name->base, headers_sorted[i + 1].name->len)) {
            ++i;
            v = mrb_str_cat_lit(mrb, v, "\n");
            v = mrb_str_cat(mrb, v, headers_sorted[i].value.base, headers_sorted[i].value.len);
        }
        mrb_hash_set(mrb, headers_hash, k, v);
    }
    mrb_ary_set(mrb, resp, 1, headers_hash);

    /* set input stream */
    assert(mrb_nil_p(ctx->refs.input_stream));
    mrb_value input_stream_class;
    if (ctx->req.method_is_head || status == 101 || status == 204 || status == 304) {
        input_stream_class = mrb_ary_entry(ctx->ctx->shared->constants, H2O_MRUBY_HTTP_EMPTY_INPUT_STREAM_CLASS);
    } else {
        input_stream_class = mrb_ary_entry(ctx->ctx->shared->constants, H2O_MRUBY_HTTP_INPUT_STREAM_CLASS);
    }
    ctx->refs.input_stream = h2o_mruby_create_data_instance(mrb, input_stream_class, ctx, &input_stream_type);
    mrb_ary_set(mrb, resp, 2, ctx->refs.input_stream);

    if (mrb_nil_p(ctx->receiver)) {
        /* is async */
        mrb_funcall(mrb, ctx->refs.request, "_set_response", 1, resp);
        if (mrb->exc != NULL) {
            h2o_fatal("_set_response failed\n");
        }
    } else {
        /* send response to the waiting receiver */
        h2o_mruby_run_fiber(ctx->ctx, detach_receiver(ctx), resp, NULL);
    }

    mrb_gc_arena_restore(mrb, gc_arena);
}