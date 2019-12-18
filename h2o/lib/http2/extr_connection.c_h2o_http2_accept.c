#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_13__ {TYPE_1__* input; TYPE_3__* data; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_14__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  http2_origin_frame; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;
struct TYPE_15__ {int /*<<< orphan*/  http2_origin_frame; int /*<<< orphan*/  hosts; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_4__ h2o_accept_ctx_t ;
struct TYPE_12__ {scalar_t__ size; } ;

/* Variables and functions */
 TYPE_3__* create_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,struct timeval) ; 
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_2__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  on_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_idle_timeout (TYPE_3__*) ; 

void h2o_http2_accept(h2o_accept_ctx_t *ctx, h2o_socket_t *sock, struct timeval connected_at)
{
    h2o_http2_conn_t *conn = create_conn(ctx->ctx, ctx->hosts, sock, connected_at);
    conn->http2_origin_frame = ctx->http2_origin_frame;
    sock->data = conn;
    h2o_socket_read_start(conn->sock, on_read);
    update_idle_timeout(conn);
    if (sock->input->size != 0)
        on_read(sock, 0);
}