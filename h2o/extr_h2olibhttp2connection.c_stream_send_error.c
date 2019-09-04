#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  buf; } ;
struct TYPE_12__ {TYPE_3__* ctx; } ;
struct TYPE_14__ {scalar_t__ state; TYPE_5__ _write; TYPE_4__ super; } ;
typedef  TYPE_6__ h2o_http2_conn_t ;
struct TYPE_9__ {int /*<<< orphan*/ * protocol_level_errors; } ;
struct TYPE_10__ {TYPE_1__ events; } ;
struct TYPE_11__ {TYPE_2__ http2; } ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_CONN_STATE_IS_CLOSING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_http2_conn_request_write (TYPE_6__*) ; 
 int /*<<< orphan*/  h2o_http2_encode_rst_stream_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stream_send_error(h2o_http2_conn_t *conn, uint32_t stream_id, int errnum)
{
    assert(stream_id != 0);
    assert(conn->state < H2O_HTTP2_CONN_STATE_IS_CLOSING);

    conn->super.ctx->http2.events.protocol_level_errors[-errnum]++;

    h2o_http2_encode_rst_stream_frame(&conn->_write.buf, stream_id, -errnum);
    h2o_http2_conn_request_write(conn);
}