#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  command; } ;
struct st_h2o_mruby_redis_command_context_t {TYPE_3__* client; TYPE_2__ refs; int /*<<< orphan*/  receiver; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_8__ {TYPE_1__* shared; } ;
struct TYPE_7__ {TYPE_4__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_receiver (struct st_h2o_mruby_redis_command_context_t*,int) ; 
 int /*<<< orphan*/  h2o_mruby_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_run_fiber (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pass_reply(struct st_h2o_mruby_redis_command_context_t *ctx, mrb_value reply)
{
    mrb_state *mrb = ctx->client->ctx->shared->mrb;
    if (mrb_nil_p(ctx->receiver)) {
        mrb_funcall(mrb, ctx->refs.command, "_on_reply", 1, reply);
        h2o_mruby_assert(mrb);
    } else {
        h2o_mruby_run_fiber(ctx->client->ctx, detach_receiver(ctx, 1), reply, NULL);
    }
}