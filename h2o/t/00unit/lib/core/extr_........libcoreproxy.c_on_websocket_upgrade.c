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
typedef  int /*<<< orphan*/  uint64_t ;
struct rp_ws_upgrade_info_t {int /*<<< orphan*/  ctx; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * upstream_sock; } ;
struct rp_generator_t {TYPE_3__* client; TYPE_2__* src_req; } ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_6__ {TYPE_1__* conn; } ;
typedef  TYPE_2__ h2o_req_t ;
struct TYPE_7__ {int /*<<< orphan*/ * (* steal_socket ) (TYPE_3__*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_http1_upgrade (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rp_ws_upgrade_info_t*) ; 
 struct rp_ws_upgrade_info_t* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  on_websocket_upgrade_complete ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*) ; 

__attribute__((used)) static inline void on_websocket_upgrade(struct rp_generator_t *self, uint64_t timeout)
{
    h2o_req_t *req = self->src_req;
    h2o_socket_t *sock = self->client->steal_socket(self->client);
    struct rp_ws_upgrade_info_t *info = h2o_mem_alloc(sizeof(*info));
    info->upstream_sock = sock;
    info->timeout = timeout;
    info->ctx = req->conn->ctx;
    h2o_http1_upgrade(req, NULL, 0, on_websocket_upgrade_complete, info);
}