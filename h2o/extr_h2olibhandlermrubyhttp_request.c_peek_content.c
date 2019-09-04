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
struct TYPE_6__ {int /*<<< orphan*/ * after_closed; scalar_t__ has_content; } ;
struct TYPE_7__ {TYPE_2__ resp; TYPE_1__* client; } ;
typedef  TYPE_3__ h2o_mruby_http_request_context_t ;
typedef  int /*<<< orphan*/  h2o_buffer_t ;
struct TYPE_5__ {int /*<<< orphan*/ ** buf; } ;

/* Variables and functions */

__attribute__((used)) static h2o_buffer_t **peek_content(h2o_mruby_http_request_context_t *ctx, int *is_final)
{
    *is_final = ctx->client == NULL;
    return ctx->client != NULL && ctx->resp.has_content ? ctx->client->buf : &ctx->resp.after_closed;
}