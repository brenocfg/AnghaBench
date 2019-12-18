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
struct st_h2o_http2client_stream_t {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
struct st_h2o_http2client_conn_t {scalar_t__ max_open_stream_id; TYPE_1__ output; } ;
struct TYPE_8__ {int /*<<< orphan*/  window_size_increment; } ;
typedef  TYPE_2__ h2o_http2_window_update_payload_t ;
struct TYPE_9__ {scalar_t__ stream_id; } ;
typedef  TYPE_3__ h2o_http2_frame_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FLOW_CONTROL ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int /*<<< orphan*/  call_callback_with_error (struct st_h2o_http2client_stream_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http2client_stream_t*) ; 
 scalar_t__ conn_get_buffer_window (struct st_h2o_http2client_conn_t*) ; 
 struct st_h2o_http2client_stream_t* get_stream (struct st_h2o_http2client_conn_t*,scalar_t__) ; 
 int h2o_http2_decode_window_update_payload (TYPE_2__*,TYPE_3__*,char const**,int*) ; 
 scalar_t__ h2o_http2_window_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_httpclient_error_flow_control ; 
 int /*<<< orphan*/  h2o_httpclient_error_http2_protocol_violation ; 
 int /*<<< orphan*/  request_write (struct st_h2o_http2client_conn_t*) ; 
 int /*<<< orphan*/  stream_send_error (struct st_h2o_http2client_conn_t*,scalar_t__,int) ; 
 scalar_t__ update_stream_output_window (struct st_h2o_http2client_stream_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_window_update_frame(struct st_h2o_http2client_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_window_update_payload_t payload;
    int ret, err_is_stream_level;

    if ((ret = h2o_http2_decode_window_update_payload(&payload, frame, err_desc, &err_is_stream_level)) != 0) {
        if (err_is_stream_level) {
            stream_send_error(conn, frame->stream_id, ret);
            struct st_h2o_http2client_stream_t *stream = get_stream(conn, frame->stream_id);
            if (stream != NULL) {
                call_callback_with_error(stream, h2o_httpclient_error_http2_protocol_violation);
                close_stream(stream);
            }
            return 0;
        } else {
            return ret;
        }
    }

    if (frame->stream_id == 0) {
        if (h2o_http2_window_update(&conn->output.window, payload.window_size_increment) != 0) {
            *err_desc = "flow control window overflow";
            return H2O_HTTP2_ERROR_FLOW_CONTROL;
        }
    } else if (frame->stream_id <= conn->max_open_stream_id) {
        struct st_h2o_http2client_stream_t *stream = get_stream(conn, frame->stream_id);
        if (stream != NULL) {
            if (update_stream_output_window(stream, payload.window_size_increment) != 0) {
                stream_send_error(conn, frame->stream_id, H2O_HTTP2_ERROR_FLOW_CONTROL);
                call_callback_with_error(stream, h2o_httpclient_error_flow_control);
                close_stream(stream);
                return 0;
            }
        }
    } else {
        *err_desc = "invalid stream id in WINDOW_UPDATE frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if (conn_get_buffer_window(conn) > 0)
        request_write(conn);

    return 0;
}