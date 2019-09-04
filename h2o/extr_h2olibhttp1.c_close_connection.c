#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_h2o_http1_conn_t {int /*<<< orphan*/  _conns; int /*<<< orphan*/ * sock; int /*<<< orphan*/  req; int /*<<< orphan*/  _timeout_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_http1_conn_t*) ; 
 int /*<<< orphan*/  h2o_dispose_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_connection(struct st_h2o_http1_conn_t *conn, int close_socket)
{
    h2o_timer_unlink(&conn->_timeout_entry);
    h2o_dispose_request(&conn->req);
    if (conn->sock != NULL && close_socket)
        h2o_socket_close(conn->sock);
    h2o_linklist_unlink(&conn->_conns);
    free(conn);
}