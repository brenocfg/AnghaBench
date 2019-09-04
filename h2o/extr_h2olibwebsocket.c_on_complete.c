#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sock; int /*<<< orphan*/  (* cb ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ h2o_websocket_conn_t ;
struct TYPE_7__ {int /*<<< orphan*/  input; TYPE_1__* data; } ;
typedef  TYPE_2__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_buffer_consume (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  h2o_websocket_proceed (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_complete(void *user_data, h2o_socket_t *sock, size_t reqsize)
{
    h2o_websocket_conn_t *conn = user_data;

    /* close the connection on error */
    if (sock == NULL) {
        (*conn->cb)(conn, NULL);
        return;
    }

    conn->sock = sock;
    sock->data = conn;
    h2o_buffer_consume(&sock->input, reqsize);
    h2o_websocket_proceed(conn);
}