#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* data; int /*<<< orphan*/  (* cb ) (void*,TYPE_2__*,size_t) ;} ;
struct st_h2o_http1_conn_t {size_t _unconsumed_request_size; TYPE_2__* sock; TYPE_1__ upgrade; } ;
struct TYPE_6__ {struct st_h2o_http1_conn_t* data; } ;
typedef  TYPE_2__ h2o_socket_t ;
typedef  int /*<<< orphan*/  (* h2o_http1_upgrade_cb ) (void*,TYPE_2__*,size_t) ;

/* Variables and functions */
 int /*<<< orphan*/  close_connection (struct st_h2o_http1_conn_t*,int) ; 

__attribute__((used)) static void on_upgrade_complete(h2o_socket_t *socket, const char *err)
{
    struct st_h2o_http1_conn_t *conn = socket->data;
    h2o_http1_upgrade_cb cb = conn->upgrade.cb;
    void *data = conn->upgrade.data;
    h2o_socket_t *sock = NULL;
    size_t headers_size = 0;

    /* destruct the connection (after detaching the socket) */
    if (err == 0) {
        sock = conn->sock;
        headers_size = conn->_unconsumed_request_size;
        close_connection(conn, 0);
    } else {
        close_connection(conn, 1);
    }

    cb(data, sock, headers_size);
}