#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_27__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_11__ ;

/* Type definitions */
struct TYPE_33__ {TYPE_27__* body; } ;
struct TYPE_32__ {TYPE_4__* ctx; int /*<<< orphan*/  on_streaming_selected; int /*<<< orphan*/  cb; } ;
struct TYPE_34__ {TYPE_3__ _req_body; TYPE_2__ write_req; int /*<<< orphan*/  entity; } ;
struct TYPE_29__ {scalar_t__ dependency; } ;
struct TYPE_35__ {scalar_t__ state; TYPE_4__ req; TYPE_11__ received_priority; } ;
typedef  TYPE_5__ h2o_http2_stream_t ;
struct TYPE_36__ {int /*<<< orphan*/  headers_len; int /*<<< orphan*/  headers; TYPE_11__ priority; } ;
typedef  TYPE_6__ h2o_http2_headers_payload_t ;
struct TYPE_37__ {int stream_id; int flags; } ;
typedef  TYPE_7__ h2o_http2_frame_t ;
struct TYPE_30__ {int max_open; } ;
struct TYPE_38__ {TYPE_27__* _headers_unparsed; int /*<<< orphan*/  _read_expect; TYPE_1__ pull_stream_ids; } ;
typedef  TYPE_8__ h2o_http2_conn_t ;
struct TYPE_31__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_PROTOCOL ; 
 int H2O_HTTP2_ERROR_STREAM_CLOSED ; 
 int H2O_HTTP2_FRAME_FLAG_END_HEADERS ; 
 int H2O_HTTP2_FRAME_FLAG_END_STREAM ; 
 int H2O_HTTP2_FRAME_FLAG_PRIORITY ; 
 scalar_t__ H2O_HTTP2_STREAM_STATE_RECV_BODY ; 
 int /*<<< orphan*/  expect_continuation_of_headers ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_27__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_reserve (TYPE_27__**,int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_http2_conn_get_stream (TYPE_8__*,int) ; 
 int h2o_http2_decode_headers_payload (TYPE_6__*,TYPE_7__*,char const**) ; 
 TYPE_5__* h2o_http2_stream_open (TYPE_8__*,int,int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  h2o_http2_stream_prepare_for_request (TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  h2o_write_req_first ; 
 int handle_incoming_request (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int handle_trailing_headers (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_request_streaming_selected ; 
 int /*<<< orphan*/  set_priority (TYPE_8__*,TYPE_5__*,TYPE_11__*,int) ; 

__attribute__((used)) static int handle_headers_frame(h2o_http2_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_headers_payload_t payload;
    h2o_http2_stream_t *stream;
    int ret;

    /* decode */
    if ((ret = h2o_http2_decode_headers_payload(&payload, frame, err_desc)) != 0)
        return ret;
    if ((frame->stream_id & 1) == 0) {
        *err_desc = "invalid stream id in HEADERS frame";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }
    if (!(conn->pull_stream_ids.max_open < frame->stream_id)) {
        if ((stream = h2o_http2_conn_get_stream(conn, frame->stream_id)) != NULL &&
            stream->state == H2O_HTTP2_STREAM_STATE_RECV_BODY) {
            /* is a trailer */
            if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) == 0) {
                *err_desc = "trailing HEADERS frame MUST have END_STREAM flag set";
                return H2O_HTTP2_ERROR_PROTOCOL;
            }
            stream->req.entity = h2o_iovec_init(stream->req._req_body.body->bytes, stream->req._req_body.body->size);
            if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) == 0)
                goto PREPARE_FOR_CONTINUATION;
            return handle_trailing_headers(conn, stream, payload.headers, payload.headers_len, err_desc);
        } else {
            *err_desc = "invalid stream id in HEADERS frame";
            return H2O_HTTP2_ERROR_STREAM_CLOSED;
        }
    }
    if (frame->stream_id == payload.priority.dependency) {
        *err_desc = "stream cannot depend on itself";
        return H2O_HTTP2_ERROR_PROTOCOL;
    }

    /* open or determine the stream and prepare */
    if ((stream = h2o_http2_conn_get_stream(conn, frame->stream_id)) != NULL) {
        if ((frame->flags & H2O_HTTP2_FRAME_FLAG_PRIORITY) != 0) {
            set_priority(conn, stream, &payload.priority, 1);
            stream->received_priority = payload.priority;
        }
    } else {
        stream = h2o_http2_stream_open(conn, frame->stream_id, NULL, &payload.priority);
        set_priority(conn, stream, &payload.priority, 0);
    }
    h2o_http2_stream_prepare_for_request(conn, stream);
    stream->req.write_req.cb = h2o_write_req_first;
    stream->req.write_req.on_streaming_selected = on_request_streaming_selected;
    stream->req.write_req.ctx = &stream->req;

    /* setup container for request body if it is expected to arrive */
    if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_STREAM) == 0)
        h2o_buffer_init(&stream->req._req_body.body, &h2o_socket_buffer_prototype);

    if ((frame->flags & H2O_HTTP2_FRAME_FLAG_END_HEADERS) != 0) {
        /* request headers are complete, handle it */
        return handle_incoming_request(conn, stream, payload.headers, payload.headers_len, err_desc);
    }

PREPARE_FOR_CONTINUATION:
    /* request is not complete, store in buffer */
    conn->_read_expect = expect_continuation_of_headers;
    h2o_buffer_init(&conn->_headers_unparsed, &h2o_socket_buffer_prototype);
    h2o_buffer_reserve(&conn->_headers_unparsed, payload.headers_len);
    memcpy(conn->_headers_unparsed->bytes, payload.headers, payload.headers_len);
    conn->_headers_unparsed->size = payload.headers_len;
    return 0;
}