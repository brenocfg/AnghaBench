#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_sendvec_t ;
typedef  scalar_t__ h2o_send_state_t ;
struct TYPE_8__ {scalar_t__ send_server_timing; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/ * entries; } ;
struct TYPE_9__ {scalar_t__ send_state; scalar_t__ state; TYPE_2__ req; TYPE_1__ _data; int /*<<< orphan*/  _data_off; int /*<<< orphan*/  output_window; } ;
typedef  TYPE_3__ h2o_http2_stream_t ;
typedef  int /*<<< orphan*/  h2o_http2_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP2_STREAM_STATE_END_STREAM ; 
 scalar_t__ H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL ; 
 scalar_t__ H2O_SEND_STATE_ERROR ; 
 int /*<<< orphan*/  h2o_http2_stream_set_state (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_http2_window_get_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * send_data (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 

void h2o_http2_stream_send_pending_data(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    if (h2o_http2_window_get_avail(&stream->output_window) <= 0)
        return;

    h2o_send_state_t send_state = stream->send_state;
    h2o_sendvec_t *nextbuf =
        send_data(conn, stream, stream->_data.entries, stream->_data.size, &stream->_data_off, stream->send_state);
    if (nextbuf == NULL) {
        /* error */
        stream->_data.size = 0;
        stream->send_state = H2O_SEND_STATE_ERROR;
        h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_END_STREAM);
    } else if (nextbuf == stream->_data.entries + stream->_data.size) {
        /* sent all data */
        stream->_data.size = 0;
        if (stream->state == H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL)
            h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_END_STREAM);
    } else if (nextbuf != stream->_data.entries) {
        /* adjust the buffer */
        size_t newsize = stream->_data.size - (nextbuf - stream->_data.entries);
        memmove(stream->_data.entries, nextbuf, sizeof(stream->_data.entries[0]) * newsize);
        stream->_data.size = newsize;
    }

    if (send_state == H2O_SEND_STATE_ERROR) {
        stream->req.send_server_timing = 0; /* suppress sending trailers */
    }
}