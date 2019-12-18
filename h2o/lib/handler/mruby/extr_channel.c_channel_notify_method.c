#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_h2o_mruby_channel_context_t {int /*<<< orphan*/  ctx; int /*<<< orphan*/  receivers; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_type ; 
 int /*<<< orphan*/  h2o_mruby_run_fiber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_shift (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct st_h2o_mruby_channel_context_t* mrb_data_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value channel_notify_method(mrb_state *mrb, mrb_value self)
{
    struct st_h2o_mruby_channel_context_t *ctx;
    ctx = mrb_data_get_ptr(mrb, self, &channel_type);

    if (RARRAY_LEN(ctx->receivers) != 0) {
        int gc_arena = mrb_gc_arena_save(mrb);
        mrb_value receiver = mrb_ary_shift(mrb, ctx->receivers);
        mrb_gc_protect(mrb, receiver);
        h2o_mruby_run_fiber(ctx->ctx, receiver, mrb_nil_value(), NULL);
        mrb_gc_arena_restore(mrb, gc_arena);
    }

    return mrb_nil_value();
}