#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_15__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_13__ {scalar_t__ len; } ;
struct TYPE_16__ {scalar_t__ content_length; TYPE_11__ entity; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ h2o_req_t ;
struct TYPE_17__ {TYPE_1__* shared; } ;
typedef  TYPE_4__ h2o_mruby_context_t ;
struct TYPE_14__ {TYPE_2__* mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ SIZE_MAX ; 
 TYPE_11__ h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_11__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exc_new_str_lit (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_2__*,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 void* mrb_obj_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_respond_to (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_subreq_entity(h2o_req_t *subreq, h2o_mruby_context_t *ctx, mrb_value rack_input)
{
    mrb_state *mrb = ctx->shared->mrb;

    if (mrb_nil_p(rack_input)) {
        subreq->entity = h2o_iovec_init(NULL, 0);
        subreq->content_length = 0;
        return;
    }

    // TODO: fastpath?
    if (!mrb_respond_to(mrb, rack_input, mrb_intern_lit(mrb, "read"))) {
        mrb->exc = mrb_obj_ptr(mrb_exc_new_str_lit(mrb, E_RUNTIME_ERROR, "'rack.input' must respond to 'read'"));
        return;
    }
    mrb_value body = mrb_funcall(mrb, rack_input, "read", 0);
    if (mrb->exc != NULL)
        return;
    if (!mrb_string_p(body)) {
        mrb->exc = mrb_obj_ptr(mrb_exc_new_str_lit(mrb, E_RUNTIME_ERROR, "return value of `read` must be a string"));
        return;
    }
    subreq->entity = h2o_strdup(&subreq->pool, RSTRING_PTR(body), RSTRING_LEN(body));

    if (subreq->content_length == SIZE_MAX) {
        subreq->content_length = subreq->entity.len;
    } else {
        if (subreq->content_length > subreq->entity.len)
            subreq->content_length = subreq->entity.len;
        else if (subreq->content_length < subreq->entity.len)
            subreq->entity.len = subreq->content_length;
    }
}