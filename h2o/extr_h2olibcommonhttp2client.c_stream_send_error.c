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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct st_h2o_http2client_conn_t {scalar_t__ state; TYPE_1__ output; } ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_http2_encode_rst_stream_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_write (struct st_h2o_http2client_conn_t*) ; 

__attribute__((used)) static void stream_send_error(struct st_h2o_http2client_conn_t *conn, uint32_t stream_id, int errnum)
{
    assert(stream_id != 0);
    assert(conn->state != H2O_HTTP2CLIENT_CONN_STATE_IS_CLOSING);

    h2o_http2_encode_rst_stream_frame(&conn->output.buf, stream_id, -errnum);
    request_write(conn);
}