#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int has_content; TYPE_3__* after_closed; } ;
struct st_h2o_mruby_http_request_context_t {int /*<<< orphan*/  ctx; int /*<<< orphan*/  receiver; int /*<<< orphan*/ * shortcut; TYPE_1__ resp; int /*<<< orphan*/ * client; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_6__ {TYPE_3__** buf; struct st_h2o_mruby_http_request_context_t* data; } ;
typedef  TYPE_2__ h2o_httpclient_t ;
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_3__ h2o_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  build_chunk (struct st_h2o_mruby_http_request_context_t*) ; 
 int /*<<< orphan*/  detach_receiver (struct st_h2o_mruby_http_request_context_t*) ; 
 int /*<<< orphan*/  h2o_mruby_run_fiber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_shortcut_notify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_on_body(h2o_httpclient_t *client, const char *errstr)
{
    struct st_h2o_mruby_http_request_context_t *ctx = client->data;

    if (errstr != NULL) {
        h2o_buffer_t *tmp = ctx->resp.after_closed;
        ctx->resp.after_closed = *client->buf;
        *client->buf = tmp;
        ctx->client = NULL;
        ctx->resp.has_content = 1;
    } else if ((*client->buf)->size != 0) {
        ctx->resp.has_content = 1;
    }

    if (ctx->resp.has_content) {
        if (ctx->shortcut != NULL) {
            on_shortcut_notify(ctx->shortcut);
        } else if (!mrb_nil_p(ctx->receiver)) {
            mrb_value chunk = build_chunk(ctx);
            h2o_mruby_run_fiber(ctx->ctx, detach_receiver(ctx), chunk, NULL);
        }
    }

    return 0;
}