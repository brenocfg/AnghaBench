#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  input_stream; int /*<<< orphan*/  request; } ;
struct st_h2o_mruby_http_request_context_t {TYPE_1__ refs; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  dispose_context (struct st_h2o_mruby_http_request_context_t*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static void on_gc_dispose_request(mrb_state *mrb, void *_ctx)
{
    struct st_h2o_mruby_http_request_context_t *ctx = _ctx;
    if (ctx == NULL)
        return;
    ctx->refs.request = mrb_nil_value();
    if (mrb_nil_p(ctx->refs.input_stream))
        dispose_context(ctx);
}