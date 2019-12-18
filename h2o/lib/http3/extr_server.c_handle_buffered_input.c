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
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_12__ {scalar_t__ content_length; scalar_t__ req_body_bytes_received; TYPE_2__ write_req; int /*<<< orphan*/  process_called; } ;
struct TYPE_10__ {int (* handle_input ) (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ;TYPE_9__* buf; } ;
struct st_h2o_http3_server_stream_t {int state; int read_blocked; int /*<<< orphan*/  link; TYPE_4__* req_body; TYPE_3__ req; TYPE_6__* quic; TYPE_1__ recvbuf; } ;
struct TYPE_14__ {int /*<<< orphan*/  req_streaming; int /*<<< orphan*/  recv_body_blocked; int /*<<< orphan*/  pending; } ;
struct st_h2o_http3_server_conn_t {TYPE_5__ delayed_streams; } ;
struct TYPE_16__ {size_t size; scalar_t__ bytes; } ;
struct TYPE_15__ {int /*<<< orphan*/  recvstate; } ;
struct TYPE_13__ {scalar_t__ size; } ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_GENERAL_PROTOCOL ; 
 int H2O_HTTP3_ERROR_INCOMPLETE ; 
 int H2O_HTTP3_ERROR_REQUEST_INCOMPLETE ; 
 scalar_t__ H2O_HTTP3_REQUEST_BODY_MIN_BYTES_TO_BLOCK ; 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT ; 
#define  H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BEFORE_BLOCK 130 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BLOCKED ; 
#define  H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_UNBLOCKED 129 
#define  H2O_HTTP3_SERVER_STREAM_STATE_RECV_HEADERS 128 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_REQ_PENDING ; 
 int H2O_HTTP3_SERVER_STREAM_STATE_SEND_HEADERS ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_run_blocked (struct st_h2o_http3_server_conn_t*) ; 
 struct st_h2o_http3_server_conn_t* get_conn (struct st_h2o_http3_server_stream_t*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_9__**,size_t) ; 
 int /*<<< orphan*/  h2o_linklist_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int handle_input_expect_data (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int handle_input_post_trailers (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 size_t quicly_recvstate_bytes_available (int /*<<< orphan*/ *) ; 
 scalar_t__ quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_6__*,int) ; 
 scalar_t__ quicly_stop_requested (TYPE_6__*) ; 
 int /*<<< orphan*/  quicly_stream_sync_recvbuf (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  request_run_delayed (struct st_h2o_http3_server_conn_t*) ; 
 int /*<<< orphan*/  set_state (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/ ) ; 
 int stub1 (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 

__attribute__((used)) static int handle_buffered_input(struct st_h2o_http3_server_stream_t *stream, const char **err_desc)
{
    struct st_h2o_http3_server_conn_t *conn = get_conn(stream);
    size_t bytes_available = quicly_recvstate_bytes_available(&stream->quic->recvstate);
    assert(bytes_available <= stream->recvbuf.buf->size);
    const uint8_t *src = (const uint8_t *)stream->recvbuf.buf->bytes, *src_end = src + bytes_available;
    int ret = 0;

    /* consume contiguous bytes */
    if (quicly_stop_requested(stream->quic)) {
        src = src_end;
    } else {
        while (src != src_end) {
            if ((ret = stream->recvbuf.handle_input(stream, &src, src_end, err_desc)) != 0)
                break;
            if (quicly_stop_requested(stream->quic)) {
                src = src_end;
                break;
            }
        }
    }
    if (!(ret == 0 || ret == H2O_HTTP3_ERROR_INCOMPLETE))
        return ret;
    size_t bytes_consumed = src - (const uint8_t *)stream->recvbuf.buf->bytes;
    h2o_buffer_consume(&stream->recvbuf.buf, bytes_consumed);
    quicly_stream_sync_recvbuf(stream->quic, bytes_consumed);
    if (quicly_stop_requested(stream->quic))
        return 0;

    if (quicly_recvstate_transfer_complete(&stream->quic->recvstate)) {
        if (ret != 0) {
            /* partial frame */
            assert(ret == H2O_HTTP3_ERROR_INCOMPLETE);
            quicly_reset_stream(stream->quic, H2O_HTTP3_ERROR_GENERAL_PROTOCOL);
            set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
        } else if (stream->recvbuf.buf->size == 0 && (stream->recvbuf.handle_input == handle_input_expect_data ||
                                                      stream->recvbuf.handle_input == handle_input_post_trailers)) {
            /* have complete request, advance the state and process the request */
            if (stream->req.content_length != SIZE_MAX && stream->req.content_length != stream->req.req_body_bytes_received) {
                quicly_reset_stream(stream->quic, stream->req.req_body_bytes_received < stream->req.content_length
                                                      ? H2O_HTTP3_ERROR_INCOMPLETE
                                                      : H2O_HTTP3_ERROR_GENERAL_PROTOCOL);
                set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
            } else {
                if (stream->req.write_req.cb != NULL) {
                    if (!h2o_linklist_is_linked(&stream->link))
                        h2o_linklist_insert(&conn->delayed_streams.req_streaming, &stream->link);
                    request_run_delayed(conn);
                } else if (!stream->req.process_called && stream->state < H2O_HTTP3_SERVER_STREAM_STATE_SEND_HEADERS) {
                    /* process the request, if we haven't called h2o_process_request nor send an error response */
                    switch (stream->state) {
                    case H2O_HTTP3_SERVER_STREAM_STATE_RECV_HEADERS:
                    case H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BEFORE_BLOCK:
                    case H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_UNBLOCKED:
                        break;
                    default:
                        assert(!"unexpected state");
                        break;
                    }
                    set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_REQ_PENDING);
                    h2o_linklist_insert(&conn->delayed_streams.pending, &stream->link);
                    request_run_delayed(conn);
                }
            }
        } else {
            quicly_reset_stream(stream->quic, H2O_HTTP3_ERROR_REQUEST_INCOMPLETE);
            set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
        }
    } else {
        if (stream->state == H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BEFORE_BLOCK && stream->req_body != NULL &&
            stream->req_body->size >= H2O_HTTP3_REQUEST_BODY_MIN_BYTES_TO_BLOCK) {
            /* switch to blocked state if the request body is becoming large (this limits the concurrency to the backend) */
            stream->read_blocked = 1;
            h2o_linklist_insert(&conn->delayed_streams.recv_body_blocked, &stream->link);
            set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BLOCKED);
            check_run_blocked(conn);
        } else if (stream->req.write_req.cb != NULL && stream->req_body->size != 0) {
            /* in streaming mode, let the run_delayed invoke write_req */
            if (!h2o_linklist_is_linked(&stream->link))
                h2o_linklist_insert(&conn->delayed_streams.req_streaming, &stream->link);
            request_run_delayed(conn);
        }
    }

    return 0;
}