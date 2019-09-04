#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  input_stream; int /*<<< orphan*/  request; } ;
struct TYPE_10__ {int /*<<< orphan*/ * client; TYPE_3__ refs; TYPE_2__* ctx; } ;
typedef  TYPE_4__ h2o_mruby_http_request_context_t ;
struct TYPE_8__ {TYPE_1__* shared; } ;
struct TYPE_7__ {int /*<<< orphan*/  mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispose_context (TYPE_4__*) ; 
 int /*<<< orphan*/  mrb_basic_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_object_dead_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_dispose_context(h2o_mruby_http_request_context_t *ctx)
{
#define IS_NIL_OR_DEAD(o) (mrb_nil_p(o) || mrb_object_dead_p(ctx->ctx->shared->mrb, mrb_basic_ptr(o)))
    if (IS_NIL_OR_DEAD(ctx->refs.request) && IS_NIL_OR_DEAD(ctx->refs.input_stream)) {
        ctx->client = NULL;
        dispose_context(ctx);
        return 1;
    }
    return 0;
#undef IS_NIL_OR_DEAD
}