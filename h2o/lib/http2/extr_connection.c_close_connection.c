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
struct TYPE_5__ {int /*<<< orphan*/  timeout_entry; int /*<<< orphan*/ * buf_in_flight; } ;
struct TYPE_6__ {TYPE_1__ _write; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ h2o_http2_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP2_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  close_connection_now (TYPE_2__*) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 

int close_connection(h2o_http2_conn_t *conn)
{
    conn->state = H2O_HTTP2_CONN_STATE_IS_CLOSING;

    if (conn->_write.buf_in_flight != NULL || h2o_timer_is_linked(&conn->_write.timeout_entry)) {
        /* there is a pending write, let on_write_complete actually close the connection */
    } else {
        close_connection_now(conn);
        return -1;
    }
    return 0;
}