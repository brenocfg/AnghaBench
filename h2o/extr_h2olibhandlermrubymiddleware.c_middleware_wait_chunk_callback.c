#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_mruby_subreq_t {scalar_t__ state; int /*<<< orphan*/  receiver; TYPE_4__* buf; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_6__ {TYPE_1__* shared; } ;
typedef  TYPE_2__ h2o_mruby_context_t ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;
struct TYPE_5__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 scalar_t__ FINAL_RECEIVED ; 
 int /*<<< orphan*/  app_input_stream_type ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_4__**,scalar_t__) ; 
 int /*<<< orphan*/  h2o_mruby_new_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct st_mruby_subreq_t* mrb_data_check_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_exc_new_str_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_gc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value middleware_wait_chunk_callback(h2o_mruby_context_t *mctx, mrb_value input, mrb_value *receiver, mrb_value args,
                                                int *run_again)
{
    mrb_state *mrb = mctx->shared->mrb;
    struct st_mruby_subreq_t *subreq;

    mrb_value obj = mrb_ary_entry(args, 0);
    if (DATA_PTR(obj) == NULL) {
        return mrb_exc_new_str_lit(mrb, E_ARGUMENT_ERROR, "downstream HTTP closed");
    } else if ((subreq = mrb_data_check_get_ptr(mrb, obj, &app_input_stream_type)) == NULL) {
        return mrb_exc_new_str_lit(mrb, E_ARGUMENT_ERROR, "AppInputStream#each wrong self");
    }

    if (subreq->buf->size != 0) {
        *run_again = 1;
        mrb_value chunk = h2o_mruby_new_str(mrb, subreq->buf->bytes, subreq->buf->size);
        h2o_buffer_consume(&subreq->buf, subreq->buf->size);
        return chunk;
    } else if (subreq->state == FINAL_RECEIVED) {
        *run_again = 1;
        return mrb_nil_value();
    } else {
        assert(mrb_nil_p(subreq->receiver));
        subreq->receiver = *receiver;
        mrb_gc_register(mrb, *receiver);
        return mrb_nil_value();
    }
}