#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  request; } ;
struct TYPE_19__ {int /*<<< orphan*/  overrides; int /*<<< orphan*/  path; int /*<<< orphan*/  authority; int /*<<< orphan*/  scheme; int /*<<< orphan*/  method; } ;
struct st_mruby_subreq_t {TYPE_2__ refs; TYPE_4__ super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_18__ {int /*<<< orphan*/ * exc; TYPE_5__* ud; } ;
typedef  TYPE_3__ mrb_state ;
typedef  TYPE_4__ h2o_req_t ;
struct TYPE_20__ {TYPE_6__* current_context; } ;
typedef  TYPE_5__ h2o_mruby_shared_context_t ;
struct TYPE_21__ {TYPE_1__* shared; } ;
typedef  TYPE_6__ h2o_mruby_context_t ;
struct TYPE_16__ {int /*<<< orphan*/  constants; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_MRUBY_APP_REQUEST_CLASS ; 
 int /*<<< orphan*/  app_request_type ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct st_mruby_subreq_t* create_subreq (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  h2o_delegate_request_deferred (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_mruby_create_data_instance (TYPE_3__*,int /*<<< orphan*/ ,struct st_mruby_subreq_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_reprocess_request_deferred (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exc_raise (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value middleware_request_method(mrb_state *mrb, mrb_value self)
{
    h2o_mruby_shared_context_t *shared_ctx = mrb->ud;
    h2o_mruby_context_t *ctx = shared_ctx->current_context;
    assert(ctx != NULL);

    mrb_value env;
    mrb_value reprocess;
    mrb_get_args(mrb, "H", &env);
    reprocess = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@reprocess"));

    /* create subreq */
    struct st_mruby_subreq_t *subreq = create_subreq(shared_ctx->current_context, env, mrb_bool(reprocess));
    if (mrb->exc != NULL) {
        mrb_value exc = mrb_obj_value(mrb->exc);
        mrb->exc = NULL;
        mrb_exc_raise(mrb, exc);
    }

    subreq->refs.request = h2o_mruby_create_data_instance(mrb, mrb_ary_entry(ctx->shared->constants, H2O_MRUBY_APP_REQUEST_CLASS),
                                                          subreq, &app_request_type);

    h2o_req_t *super = &subreq->super;
    if (mrb_bool(reprocess)) {
        h2o_reprocess_request_deferred(super, super->method, super->scheme, super->authority, super->path, super->overrides, 1);
    } else {
        h2o_delegate_request_deferred(super);
    }

    return subreq->refs.request;
}