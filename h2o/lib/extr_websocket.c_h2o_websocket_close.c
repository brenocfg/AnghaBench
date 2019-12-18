#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ws_ctx; int /*<<< orphan*/ * sock; } ;
typedef  TYPE_1__ h2o_websocket_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_write_buf (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wslay_event_context_free (int /*<<< orphan*/ ) ; 

void h2o_websocket_close(h2o_websocket_conn_t *conn)
{
    if (conn->sock != NULL)
        h2o_socket_close(conn->sock);
    free_write_buf(conn);
    wslay_event_context_free(conn->ws_ctx);
    free(conn);
}