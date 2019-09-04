#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_websocket_conn_t ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_websocket_proceed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_recv(h2o_socket_t *sock, const char *err)
{
    h2o_websocket_conn_t *conn = sock->data;

    if (err != NULL) {
        on_close(conn);
        return;
    }
    h2o_websocket_proceed(conn);
}