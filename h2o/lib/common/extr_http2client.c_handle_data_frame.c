#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ (* on_body ) (TYPE_7__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_21__ {TYPE_3__ _cb; int /*<<< orphan*/  ctx; } ;
struct TYPE_16__ {int /*<<< orphan*/  window; TYPE_12__* body; } ;
struct TYPE_15__ {scalar_t__ res; } ;
struct st_h2o_http2client_stream_t {scalar_t__ stream_id; TYPE_7__ super; struct st_h2o_http2client_conn_t* conn; TYPE_2__ input; TYPE_1__ state; } ;
struct TYPE_18__ {int /*<<< orphan*/  window; } ;
struct st_h2o_http2client_conn_t {scalar_t__ max_open_stream_id; TYPE_4__ input; } ;
struct TYPE_19__ {scalar_t__ stream_id; int flags; } ;
typedef  TYPE_5__ h2o_http2_frame_t ;
struct TYPE_20__ {size_t length; scalar_t__ data; } ;
typedef  TYPE_6__ h2o_http2_data_payload_t ;
struct TYPE_14__ {size_t size; } ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FLOW_CONTROL ; 
 int H2O_HTTP2_ERROR_INTERNAL ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int H2O_HTTP2_ERROR_STREAM_CLOSED ; 
 int H2O_HTTP2_FRAME_FLAG_END_STREAM ; 
 int /*<<< orphan*/  H2O_HTTP2_SETTINGS_CLIENT_CONNECTION_WINDOW_SIZE ; 
 scalar_t__ STREAM_STATE_BODY ; 
 int /*<<< orphan*/  call_callback_with_error (struct st_h2o_http2client_stream_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_response (struct st_h2o_http2client_stream_t*) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http2client_stream_t*) ; 
 int /*<<< orphan*/  do_update_window (TYPE_7__*) ; 
 int /*<<< orphan*/  enqueue_window_update (struct st_h2o_http2client_conn_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t get_max_buffer_size (int /*<<< orphan*/ ) ; 
 struct st_h2o_http2client_stream_t* get_stream (struct st_h2o_http2client_conn_t*,scalar_t__) ; 
 int /*<<< orphan*/  h2o_buffer_append (TYPE_12__**,void*,size_t) ; 
 int h2o_http2_decode_data_payload (TYPE_6__*,TYPE_5__*,char const**) ; 
 int /*<<< orphan*/  h2o_http2_window_consume_window (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * h2o_httpclient_error_flow_control ; 
 int /*<<< orphan*/  h2o_httpclient_error_http2_protocol_violation ; 
 int /*<<< orphan*/ * h2o_httpclient_error_is_eos ; 
 int /*<<< orphan*/  stream_send_error (struct st_h2o_http2client_conn_t*,scalar_t__,int) ; 
 scalar_t__ stub1 (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_7__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_data_frame(struct st_h2o_http2client_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_data_payload_t payload;
    struct st_h2o_http2client_stream_t *stream;
    int ret;

    if ((ret = h2o_http2_decode_data_payload(&payload, frame, err_desc)) != 0)
        return ret;

    /* save the input in the request body buffer, or send error (and close the stream) */
    if ((stream = get_stream(conn, frame->stream_id)) == NULL) {
        if (frame->stream_id <= conn->max_open_stream_id) {
            stream_send_error(conn, frame->stream_id, H2O_HTTP2_ERROR_STREAM_CLOSED);
            return 0;
        } else {
            *err_desc = "invalid DATA frame";
            return H2O_HTTP2_ERROR_PROTOCOL;
        }
    }

    if (stream->state.res != STREAM_STATE_BODY) {
        stream_send_error(conn, frame->stream_id, H2O_HTTP2_ERROR_PROTOCOL);
        call_callback_with_error(stream, h2o_httpclient_error_http2_protocol_violation);
        close_stream(stream);
        return 0;
    }

    size_t max_size = get_max_buffer_size(stream->super.ctx);
    if (stream->input.body->size + payload.length > max_size) {
        stream->super._cb.on_body(&stream->super, h2o_httpclient_error_flow_control);
        stream_send_error(stream->conn, stream->stream_id, H2O_HTTP2_ERROR_FLOW_CONTROL);
        close_stream(stream);
        return 0;
    }

    h2o_buffer_append(&stream->input.body, (void *)payload.data, payload.length);

    h2o_http2_window_consume_window(&conn->input.window, payload.length);
    h2o_http2_window_consume_window(&stream->input.window, payload.length);

    int is_final = (frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) != 0;
    if (stream->super._cb.on_body(&stream->super, is_final ? h2o_httpclient_error_is_eos : NULL) != 0) {
        stream_send_error(conn, frame->stream_id, H2O_HTTP2_ERROR_INTERNAL);
        close_stream(stream);
        return 0;
    }

    if (is_final) {
        close_response(stream);
    } else {
        /* update connection-level window */
        enqueue_window_update(stream->conn, 0, &stream->conn->input.window, H2O_HTTP2_SETTINGS_CLIENT_CONNECTION_WINDOW_SIZE);
        /* update stream-level window */
        do_update_window(&stream->super);
    }

    return 0;
}