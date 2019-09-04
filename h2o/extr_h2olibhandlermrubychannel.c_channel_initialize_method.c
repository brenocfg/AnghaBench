#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_mruby_channel_context_t {int /*<<< orphan*/  receivers; int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_8__ {TYPE_2__* ud; } ;
typedef  TYPE_1__ mrb_state ;
struct TYPE_9__ {int /*<<< orphan*/ * current_context; } ;
typedef  TYPE_2__ h2o_mruby_shared_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_type ; 
 struct st_h2o_mruby_channel_context_t* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  memset (struct st_h2o_mruby_channel_context_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_ary_new (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_data_init (int /*<<< orphan*/ ,struct st_h2o_mruby_channel_context_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_iv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value channel_initialize_method(mrb_state *mrb, mrb_value self)
{
    h2o_mruby_shared_context_t *shared_ctx = mrb->ud;

    struct st_h2o_mruby_channel_context_t *ctx;
    ctx = h2o_mem_alloc(sizeof(*ctx));

    memset(ctx, 0, sizeof(*ctx));
    assert(shared_ctx->current_context != NULL);
    ctx->ctx = shared_ctx->current_context;
    ctx->receivers = mrb_ary_new(mrb);
    mrb_gc_register(mrb, ctx->receivers);

    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@queue"), mrb_ary_new(mrb));

    mrb_data_init(self, ctx, &channel_type);

    return self;
}