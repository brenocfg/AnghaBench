#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int state; int /*<<< orphan*/  _link; TYPE_1__ _data; } ;
typedef  TYPE_2__ h2o_http2_stream_t ;
typedef  int /*<<< orphan*/  h2o_http2_conn_t ;

/* Variables and functions */
#define  H2O_HTTP2_STREAM_STATE_END_STREAM 135 
#define  H2O_HTTP2_STREAM_STATE_IDLE 134 
#define  H2O_HTTP2_STREAM_STATE_RECV_BODY 133 
#define  H2O_HTTP2_STREAM_STATE_RECV_HEADERS 132 
#define  H2O_HTTP2_STREAM_STATE_REQ_PENDING 131 
#define  H2O_HTTP2_STREAM_STATE_SEND_BODY 130 
#define  H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL 129 
#define  H2O_HTTP2_STREAM_STATE_SEND_HEADERS 128 
 int /*<<< orphan*/  h2o_http2_stream_close (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_http2_stream_set_state (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 

void h2o_http2_stream_reset(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    switch (stream->state) {
    case H2O_HTTP2_STREAM_STATE_IDLE:
    case H2O_HTTP2_STREAM_STATE_RECV_HEADERS:
    case H2O_HTTP2_STREAM_STATE_RECV_BODY:
    case H2O_HTTP2_STREAM_STATE_REQ_PENDING:
        h2o_http2_stream_close(conn, stream);
        break;
    case H2O_HTTP2_STREAM_STATE_SEND_HEADERS:
    case H2O_HTTP2_STREAM_STATE_SEND_BODY:
    case H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL:
        h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_END_STREAM);
    /* continues */
    case H2O_HTTP2_STREAM_STATE_END_STREAM:
        /* clear all the queued bufs, and close the connection in the callback */
        stream->_data.size = 0;
        if (h2o_linklist_is_linked(&stream->_link)) {
            /* will be closed in the callback */
        } else {
            h2o_http2_stream_close(conn, stream);
        }
        break;
    }
}