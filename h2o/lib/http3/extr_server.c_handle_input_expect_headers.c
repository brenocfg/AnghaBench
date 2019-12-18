#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int /*<<< orphan*/  path; int /*<<< orphan*/  authority; int /*<<< orphan*/  scheme; int /*<<< orphan*/  method; } ;
struct TYPE_22__ {scalar_t__ content_length; int /*<<< orphan*/  headers; TYPE_3__ input; int /*<<< orphan*/  pool; } ;
struct TYPE_14__ {int /*<<< orphan*/  handle_input; } ;
struct st_h2o_http3_server_stream_t {TYPE_9__ req; TYPE_8__* quic; TYPE_1__ recvbuf; } ;
struct TYPE_19__ {TYPE_5__* ctx; } ;
struct TYPE_15__ {int /*<<< orphan*/  dec; } ;
struct TYPE_13__ {TYPE_2__ qpack; } ;
struct st_h2o_http3_server_conn_t {TYPE_6__ super; TYPE_11__ h3; } ;
struct TYPE_20__ {int type; int /*<<< orphan*/  length; int /*<<< orphan*/  payload; } ;
typedef  TYPE_7__ h2o_http3_read_frame_t ;
struct TYPE_21__ {int /*<<< orphan*/  recvstate; int /*<<< orphan*/  stream_id; } ;
struct TYPE_18__ {TYPE_4__* globalconf; } ;
struct TYPE_17__ {scalar_t__ max_request_entity_size; } ;

/* Variables and functions */
 int H2O_HPACK_ENCODE_INT_MAX_LENGTH ; 
 int H2O_HTTP2_ERROR_INVALID_HEADER_CHAR ; 
 int /*<<< orphan*/  H2O_HTTP3_ERROR_EARLY_RESPONSE ; 
 int H2O_HTTP3_ERROR_FRAME_UNEXPECTED ; 
#define  H2O_HTTP3_FRAME_TYPE_DATA 128 
 int H2O_HTTP3_FRAME_TYPE_HEADERS ; 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BEFORE_BLOCK ; 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_SEND_HEADERS ; 
 int /*<<< orphan*/  H2O_HTTP3_STREAM_TYPE_REQUEST ; 
 scalar_t__ SIZE_MAX ; 
 struct st_h2o_http3_server_conn_t* get_conn (struct st_h2o_http3_server_stream_t*) ; 
 int h2o_http3_read_frame (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  h2o_http3_send_qpack_header_ack (TYPE_11__*,int /*<<< orphan*/ *,size_t) ; 
 int h2o_qpack_parse_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  h2o_send_error_400 (TYPE_9__*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_send_error_413 (TYPE_9__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_input_expect_data ; 
 int /*<<< orphan*/  quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_state (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_input_expect_headers(struct st_h2o_http3_server_stream_t *stream, const uint8_t **src, const uint8_t *src_end,
                                       const char **err_desc)
{
    struct st_h2o_http3_server_conn_t *conn = get_conn(stream);
    h2o_http3_read_frame_t frame;
    int header_exists_map, ret;
    uint8_t header_ack[H2O_HPACK_ENCODE_INT_MAX_LENGTH];
    size_t header_ack_len;

    /* read the HEADERS frame (or a frame that precedes that) */
    if ((ret = h2o_http3_read_frame(&frame, 0, H2O_HTTP3_STREAM_TYPE_REQUEST, src, src_end, err_desc)) != 0)
        return ret;
    if (frame.type != H2O_HTTP3_FRAME_TYPE_HEADERS) {
        switch (frame.type) {
        case H2O_HTTP3_FRAME_TYPE_DATA:
            return H2O_HTTP3_ERROR_FRAME_UNEXPECTED;
        default:
            break;
        }
        return 0;
    }
    stream->recvbuf.handle_input = handle_input_expect_data;

    /* parse the headers */
    if ((ret = h2o_qpack_parse_request(&stream->req.pool, get_conn(stream)->h3.qpack.dec, stream->quic->stream_id,
                                       &stream->req.input.method, &stream->req.input.scheme, &stream->req.input.authority,
                                       &stream->req.input.path, &stream->req.headers, &header_exists_map,
                                       &stream->req.content_length, NULL /* TODO cache-digests */, header_ack, &header_ack_len,
                                       frame.payload, frame.length, err_desc)) != 0) {
        /* send a 400 error when observing an invalid header character */
        if (ret == H2O_HTTP2_ERROR_INVALID_HEADER_CHAR) {
            if (!quicly_recvstate_transfer_complete(&stream->quic->recvstate))
                quicly_request_stop(stream->quic, H2O_HTTP3_ERROR_EARLY_RESPONSE);
            h2o_send_error_400(&stream->req, "Invalid Request", *err_desc, 0);
            *err_desc = NULL;
            return 0;
        }
    }
    if (header_ack_len != 0)
        h2o_http3_send_qpack_header_ack(&conn->h3, header_ack, header_ack_len);

    /* check if content-length is within the permitted bounds */
    if (stream->req.content_length != SIZE_MAX &&
        stream->req.content_length > conn->super.ctx->globalconf->max_request_entity_size) {
        if (!quicly_recvstate_transfer_complete(&stream->quic->recvstate))
            quicly_request_stop(stream->quic, H2O_HTTP3_ERROR_EARLY_RESPONSE);
        set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_SEND_HEADERS);
        h2o_send_error_413(&stream->req, "Request Entity Too Large", "request entity is too large", 0);
        return 0;
    }

    /* change state */
    set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_RECV_BODY_BEFORE_BLOCK);

    return 0;
}