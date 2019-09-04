#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_7__ {int /*<<< orphan*/  max_open; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_2__ pull_stream_ids; TYPE_1__ _write; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_CONN_STATE_HALF_CLOSED ; 
 scalar_t__ H2O_HTTP2_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  h2o_http2_conn_request_write (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_http2_encode_goaway_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enqueue_goaway(h2o_http2_conn_t *conn, int errnum, h2o_iovec_t additional_data)
{
    if (conn->state < H2O_HTTP2_CONN_STATE_IS_CLOSING) {
        /* http2 spec allows sending GOAWAY more than once (for one reason since errors may arise after sending the first one) */
        h2o_http2_encode_goaway_frame(&conn->_write.buf, conn->pull_stream_ids.max_open, errnum, additional_data);
        h2o_http2_conn_request_write(conn);
        conn->state = H2O_HTTP2_CONN_STATE_HALF_CLOSED;
    }
}