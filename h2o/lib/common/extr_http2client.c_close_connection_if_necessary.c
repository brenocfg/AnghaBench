#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ num_streams; } ;
struct st_h2o_http2client_conn_t {scalar_t__ state; TYPE_1__ super; } ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2CLIENT_CONN_STATE_HALF_CLOSED ; 
 scalar_t__ H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  close_connection_now (struct st_h2o_http2client_conn_t*) ; 

__attribute__((used)) static int close_connection_if_necessary(struct st_h2o_http2client_conn_t *conn)
{
    if (conn->state == H2O_HTTP2CLIENT_CONN_STATE_HALF_CLOSED && conn->super.num_streams == 0)
        conn->state = H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING;
    if (conn->state == H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING) {
        close_connection_now(conn);
        return 1;
    }
    return 0;
}