#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cb; } ;
struct st_timeout_ctx {TYPE_4__ _timeout; TYPE_2__* client; } ;
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ h2o_httpclient_t ;
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 scalar_t__ cur_req_body_size ; 
 int /*<<< orphan*/  delay_interval_ms ; 
 struct st_timeout_ctx* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (struct st_timeout_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout_cb ; 

__attribute__((used)) static void proceed_request(h2o_httpclient_t *client, size_t written, h2o_send_state_t send_state)
{
    if (cur_req_body_size > 0) {
        struct st_timeout_ctx *tctx;
        tctx = h2o_mem_alloc(sizeof(*tctx));
        memset(tctx, 0, sizeof(*tctx));
        tctx->client = client;
        tctx->_timeout.cb = timeout_cb;
        h2o_timer_link(client->ctx->loop, delay_interval_ms, &tctx->_timeout);
    }
}