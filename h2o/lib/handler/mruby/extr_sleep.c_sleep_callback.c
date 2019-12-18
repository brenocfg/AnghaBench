#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct st_h2o_mruby_sleep_context_t {TYPE_4__* ctx; int /*<<< orphan*/  started_at; int /*<<< orphan*/  timeout_entry; int /*<<< orphan*/  receiver; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_12__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_3__ mrb_state ;
struct TYPE_13__ {TYPE_2__* shared; } ;
typedef  TYPE_4__ h2o_mruby_context_t ;
struct TYPE_11__ {TYPE_1__* ctx; TYPE_3__* mrb; } ;
struct TYPE_10__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  E_NOMETHOD_ERROR ; 
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct st_h2o_mruby_sleep_context_t* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct st_h2o_mruby_sleep_context_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exc_new_str_lit (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int mrb_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_register (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 scalar_t__ mrb_obj_is_kind_of (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_sleep_timeout ; 

__attribute__((used)) static mrb_value sleep_callback(h2o_mruby_context_t *mctx, mrb_value input, mrb_value *receiver, mrb_value args, int *run_again)
{
    mrb_state *mrb = mctx->shared->mrb;

    assert(mrb_array_p(args));
    if (RARRAY_LEN(args) == 0) {
        return mrb_nil_value(); /* sleep forever */
    }
    mrb_value arg_sec = mrb_ary_entry(args, 0);

    /* convert the argument using to_f */
    arg_sec = mrb_funcall(mrb, arg_sec, "to_f", 0);

    if (mrb->exc) {
        *run_again = 1;
        mrb_value exc = mrb_obj_value(mrb->exc);
        if (mrb_obj_is_kind_of(mrb, exc, E_NOMETHOD_ERROR)) {
            exc = mrb_exc_new_str_lit(mrb, E_ARGUMENT_ERROR, "the argument of the sleep function must respond to 'to_f' method");
        }
        mrb->exc = NULL;
        return exc;
    }
    uint64_t msec = mrb_float(arg_sec) * 1000;

    struct st_h2o_mruby_sleep_context_t *ctx = h2o_mem_alloc(sizeof(*ctx));
    memset(ctx, 0, sizeof(*ctx));
    ctx->ctx = mctx;
    ctx->receiver = *receiver;
    h2o_timer_init(&ctx->timeout_entry, on_sleep_timeout);
    h2o_timer_link(ctx->ctx->shared->ctx->loop, msec, &ctx->timeout_entry);

    ctx->started_at = h2o_now(ctx->ctx->shared->ctx->loop);

    mrb_gc_register(mrb, *receiver);

    return mrb_nil_value();
}