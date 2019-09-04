#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cnt; } ;
struct TYPE_9__ {TYPE_1__ _write_buf; } ;
typedef  TYPE_2__ h2o_websocket_conn_t ;
struct TYPE_10__ {TYPE_2__* data; } ;
typedef  TYPE_3__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_write_buf (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_websocket_proceed (TYPE_2__*) ; 
 int /*<<< orphan*/  on_close (TYPE_2__*) ; 

__attribute__((used)) static void on_write_complete(h2o_socket_t *sock, const char *err)
{
    h2o_websocket_conn_t *conn = sock->data;

    if (err != NULL) {
        on_close(conn);
        return;
    }
    assert(conn->_write_buf.cnt > 0);
    free_write_buf(conn);
    conn->_write_buf.cnt = 0;

    h2o_websocket_proceed(conn);
}