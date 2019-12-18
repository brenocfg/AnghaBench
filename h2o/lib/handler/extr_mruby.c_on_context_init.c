#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_8__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ h2o_mruby_handler_t ;
struct TYPE_9__ {void* proc; TYPE_7__* shared; void* resumers; void* blocking_reqs; TYPE_1__* handler; } ;
typedef  TYPE_2__ h2o_mruby_context_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
typedef  int /*<<< orphan*/  h2o_context_t ;
struct TYPE_10__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_7__* get_shared_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_context_set_handler_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_mruby_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_run_fiber (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_array_p (void*) ; 
 void* mrb_ary_entry (void*,int) ; 
 void* mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_protect (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 void* prepare_fibers (TYPE_2__*) ; 

__attribute__((used)) static void on_context_init(h2o_handler_t *_handler, h2o_context_t *ctx)
{
    h2o_mruby_handler_t *handler = (void *)_handler;
    h2o_mruby_context_t *handler_ctx = h2o_mem_alloc(sizeof(*handler_ctx));

    handler_ctx->handler = handler;
    handler_ctx->shared = get_shared_context(ctx);

    mrb_state *mrb = handler_ctx->shared->mrb;

    handler_ctx->blocking_reqs = mrb_ary_new(mrb);
    handler_ctx->resumers = mrb_ary_new(mrb);

    /* compile code (must be done for each thread) */
    int arena = mrb_gc_arena_save(mrb);

    mrb_value fibers = prepare_fibers(handler_ctx);
    assert(mrb_array_p(fibers));

    handler_ctx->proc = mrb_ary_entry(fibers, 0);

    /* run configurator */
    mrb_value configurator = mrb_ary_entry(fibers, 1);
    h2o_mruby_run_fiber(handler_ctx, configurator, mrb_nil_value(), NULL);
    h2o_mruby_assert(handler_ctx->shared->mrb);

    mrb_gc_arena_restore(mrb, arena);
    mrb_gc_protect(mrb, handler_ctx->proc);
    mrb_gc_protect(mrb, configurator);

    h2o_context_set_handler_context(ctx, &handler->super, handler_ctx);
}