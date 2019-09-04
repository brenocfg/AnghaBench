#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  defer_timeout; int /*<<< orphan*/ * buf_in_flight; } ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
struct st_h2o_http2client_conn_t {TYPE_2__ output; TYPE_1__ super; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  close_connection_now (struct st_h2o_http2client_conn_t*) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int close_connection(struct st_h2o_http2client_conn_t *conn)
{
    conn->state = H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING;
    h2o_socket_read_stop(conn->super.sock);

    if (conn->output.buf_in_flight != NULL || h2o_timer_is_linked(&conn->output.defer_timeout)) {
        /* there is a pending write, let close_connection_if_necessary actually close the connection */
    } else {
        close_connection_now(conn);
        return -1;
    }
    return 0;
}