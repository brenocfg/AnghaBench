#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* conn; TYPE_5__* overrides; } ;
typedef  TYPE_4__ h2o_req_t ;
struct TYPE_11__ {int /*<<< orphan*/ * client_ctx; } ;
typedef  TYPE_5__ h2o_req_overrides_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_ctx_t ;
struct TYPE_9__ {TYPE_2__* ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  client_ctx; } ;
struct TYPE_8__ {TYPE_1__ proxy; } ;

/* Variables and functions */

__attribute__((used)) static h2o_httpclient_ctx_t *get_client_ctx(h2o_req_t *req)
{
    h2o_req_overrides_t *overrides = req->overrides;
    if (overrides != NULL && overrides->client_ctx != NULL)
        return overrides->client_ctx;
    return &req->conn->ctx->proxy.client_ctx;
}