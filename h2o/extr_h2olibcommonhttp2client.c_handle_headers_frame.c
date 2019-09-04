#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  _timeout; } ;
struct st_h2o_http2client_stream_t {int state; TYPE_2__ super; } ;
struct TYPE_13__ {TYPE_9__* headers_unparsed; void* read_frame; } ;
struct st_h2o_http2client_conn_t {TYPE_3__ input; } ;
struct TYPE_11__ {scalar_t__ dependency; } ;
struct TYPE_14__ {int /*<<< orphan*/  headers_len; int /*<<< orphan*/  headers; TYPE_1__ priority; } ;
typedef  TYPE_4__ h2o_http2_headers_payload_t ;
struct TYPE_15__ {int stream_id; int flags; } ;
typedef  TYPE_5__ h2o_http2_frame_t ;
struct TYPE_16__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
#define  H2O_HTTP2CLIENT_STREAM_STATE_RECV_BODY 129 
#define  H2O_HTTP2CLIENT_STREAM_STATE_RECV_HEADERS 128 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int H2O_HTTP2_ERROR_STREAM_CLOSED ; 
 int H2O_HTTP2_FRAME_FLAG_END_HEADERS ; 
 int H2O_HTTP2_FRAME_FLAG_END_STREAM ; 
 int /*<<< orphan*/  call_callback_with_error (struct st_h2o_http2client_stream_t*,char*) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http2client_stream_t*) ; 
 void* expect_continuation_of_headers ; 
 struct st_h2o_http2client_stream_t* get_stream (struct st_h2o_http2client_conn_t*,scalar_t__) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_9__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_reserve (TYPE_9__**,int /*<<< orphan*/ ) ; 
 int h2o_http2_decode_headers_payload (TYPE_4__*,TYPE_5__*,char const**) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int on_head (struct st_h2o_http2client_conn_t*,struct st_h2o_http2client_stream_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,int) ; 
 int /*<<< orphan*/  stream_send_error (struct st_h2o_http2client_conn_t*,scalar_t__,int) ; 

__attribute__((used)) static int handle_headers_frame(struct st_h2o_http2client_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_headers_payload_t payload;
    struct st_h2o_http2client_stream_t *stream;
    int ret;

    /* decode */
    if ((ret = h2o_http2_decode_headers_payload(&payload, frame, err_desc)) != 0)
        return ret;
    if ((frame->stream_id & 1) == 0) {
        *err_desc = "invalid stream id in HEADERS frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if (frame->stream_id == payload.priority.dependency) {
        *err_desc = "stream cannot depend on itself";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    if ((stream = get_stream(conn, frame->stream_id)) == NULL) {
        *err_desc = "invalid stream id in HEADERS frame";
        return H2O_HTTP2_ERROR_STREAM_CLOSED;
    }

    h2o_timer_unlink(&stream->super._timeout);

    switch (stream->state) {
    case H2O_HTTP2CLIENT_STREAM_STATE_RECV_HEADERS:
        break;
    case H2O_HTTP2CLIENT_STREAM_STATE_RECV_BODY:
        /* is a trailer (ignore after only validate it) */
        if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) == 0) {
            *err_desc = "trailing HEADERS frame MUST have END_STREAM flag set";
            return H2O_HTTP2_ERROR_PROTOCOL;
        }
        if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) == 0)
            /* read following continuation frames without initializing `headers_unparsed` */
            conn->input.read_frame = expect_continuation_of_headers;
        return 0;
    default:
        stream_send_error(conn, frame->stream_id, H2O_HTTP2_ERROR_PROTOCOL);
        call_callback_with_error(stream, "invalid HEADERS frame");
        close_stream(stream);
        return 0;
    }

    if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) == 0) {
        /* request is not complete, store in buffer */
        conn->input.read_frame = expect_continuation_of_headers;
        h2o_buffer_init(&conn->input.headers_unparsed, &h2o_socket_buffer_prototype);
        h2o_buffer_reserve(&conn->input.headers_unparsed, payload.headers_len);
        memcpy(conn->input.headers_unparsed->bytes, payload.headers, payload.headers_len);
        conn->input.headers_unparsed->size = payload.headers_len;
        return 0;
    }

    int is_end_stream = (frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) != 0;

    /* response header is complete, handle it */
    return on_head(conn, stream, payload.headers, payload.headers_len, err_desc, is_end_stream);
}