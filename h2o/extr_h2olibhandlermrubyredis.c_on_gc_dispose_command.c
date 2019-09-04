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
struct st_h2o_mruby_redis_command_context_t {int /*<<< orphan*/  receiver; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  detach_receiver (struct st_h2o_mruby_redis_command_context_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct st_h2o_mruby_redis_command_context_t*) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_gc_dispose_command(mrb_state *mrb, void *_ctx)
{
    struct st_h2o_mruby_redis_command_context_t *ctx = _ctx;

    if (!mrb_nil_p(ctx->receiver)) {
        detach_receiver(ctx, 0);
    }
    free(ctx);
}