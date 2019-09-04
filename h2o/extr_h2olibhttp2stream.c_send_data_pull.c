#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_send_state_t ;
struct TYPE_15__ {size_t len; scalar_t__ base; } ;
typedef  TYPE_2__ h2o_iovec_t ;
struct TYPE_16__ {int /*<<< orphan*/  _pull_cb; int /*<<< orphan*/  req; } ;
typedef  TYPE_3__ h2o_http2_stream_t ;
struct TYPE_14__ {TYPE_8__* buf; } ;
struct TYPE_17__ {TYPE_1__ _write; } ;
typedef  TYPE_4__ h2o_http2_conn_t ;
struct TYPE_18__ {scalar_t__ size; scalar_t__ bytes; } ;

/* Variables and functions */
 scalar_t__ H2O_HTTP2_FRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 size_t calc_max_payload_size (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  commit_data_header (TYPE_4__*,TYPE_3__*,TYPE_8__**,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_reserve (TYPE_8__**,scalar_t__) ; 
 int /*<<< orphan*/  h2o_pull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static h2o_send_state_t send_data_pull(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    size_t max_payload_size;
    h2o_iovec_t cbuf;
    h2o_send_state_t send_state = H2O_SEND_STATE_IN_PROGRESS;

    if ((max_payload_size = calc_max_payload_size(conn, stream)) == 0)
        goto Exit;
    /* reserve buffer */
    h2o_buffer_reserve(&conn->_write.buf, H2O_HTTP2_FRAME_HEADER_SIZE + max_payload_size);
    /* obtain content */
    cbuf.base = conn->_write.buf->bytes + conn->_write.buf->size + H2O_HTTP2_FRAME_HEADER_SIZE;
    cbuf.len = max_payload_size;
    send_state = h2o_pull(&stream->req, stream->_pull_cb, &cbuf);
    /* write the header */
    commit_data_header(conn, stream, &conn->_write.buf, cbuf.len, send_state);

Exit:
    return send_state;
}