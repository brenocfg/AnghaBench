#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rp_ws_upgrade_info_t {int /*<<< orphan*/  upstream_sock; int /*<<< orphan*/  timeout; int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rp_ws_upgrade_info_t*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_tunnel_establish (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_websocket_upgrade_complete(void *_info, h2o_socket_t *sock, size_t reqsize)
{
    struct rp_ws_upgrade_info_t *info = _info;

    if (sock != NULL) {
        h2o_buffer_consume(&sock->input, reqsize); // It is detached from conn. Let's trash unused data.
        h2o_tunnel_establish(info->ctx, sock, info->upstream_sock, info->timeout);
    } else {
        h2o_socket_close(info->upstream_sock);
    }
    free(info);
}