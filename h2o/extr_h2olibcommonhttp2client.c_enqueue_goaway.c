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
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct st_h2o_http2client_conn_t {scalar_t__ state; TYPE_2__ super; TYPE_1__ output; } ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2CLIENT_CONN_STATE_HALF_CLOSED ; 
 scalar_t__ H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  h2o_http2_encode_goaway_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_write (struct st_h2o_http2client_conn_t*) ; 

__attribute__((used)) static void enqueue_goaway(struct st_h2o_http2client_conn_t *conn, int errnum, h2o_iovec_t additional_data)
{
    if (conn->state == H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING)
        return;

    h2o_http2_encode_goaway_frame(&conn->output.buf, 0, errnum, additional_data);
    request_write(conn);
    conn->state = H2O_HTTP2CLIENT_CONN_STATE_HALF_CLOSED;

    /* stop opening new streams */
    if (h2o_linklist_is_linked(&conn->super.link))
        h2o_linklist_unlink(&conn->super.link);
}