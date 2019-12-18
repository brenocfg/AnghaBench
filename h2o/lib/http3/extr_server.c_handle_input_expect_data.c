#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {scalar_t__ bytes_left_in_data_frame; int /*<<< orphan*/  handle_input; } ;
struct TYPE_7__ {scalar_t__ content_length; scalar_t__ req_body_bytes_received; } ;
struct st_h2o_http3_server_stream_t {TYPE_2__ recvbuf; TYPE_4__* quic; TYPE_1__ req; } ;
struct TYPE_9__ {int type; scalar_t__ length; } ;
typedef  TYPE_3__ h2o_http3_read_frame_t ;
struct TYPE_10__ {int /*<<< orphan*/  sendstate; int /*<<< orphan*/  recvstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_EARLY_RESPONSE ; 
 int H2O_HTTP3_ERROR_FRAME_UNEXPECTED ; 
 int /*<<< orphan*/  H2O_HTTP3_ERROR_GENERAL_PROTOCOL ; 
#define  H2O_HTTP3_FRAME_TYPE_DATA 130 
#define  H2O_HTTP3_FRAME_TYPE_HEADERS 129 
#define  H2O_HTTP3_FRAME_TYPE_PRIORITY 128 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT ; 
 int /*<<< orphan*/  H2O_HTTP3_STREAM_TYPE_REQUEST ; 
 scalar_t__ SIZE_MAX ; 
 int h2o_http3_read_frame (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  handle_input_expect_data_payload ; 
 int /*<<< orphan*/  handle_input_post_trailers ; 
 int /*<<< orphan*/  quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendstate_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_state (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/ ) ; 

int handle_input_expect_data(struct st_h2o_http3_server_stream_t *stream, const uint8_t **src, const uint8_t *src_end,
                             const char **err_desc)
{
    h2o_http3_read_frame_t frame;
    int ret;

    /* read frame */
    if ((ret = h2o_http3_read_frame(&frame, 0, H2O_HTTP3_STREAM_TYPE_REQUEST, src, src_end, err_desc)) != 0)
        return ret;
    switch (frame.type) {
    case H2O_HTTP3_FRAME_TYPE_PRIORITY:
        return H2O_HTTP3_ERROR_FRAME_UNEXPECTED;
    case H2O_HTTP3_FRAME_TYPE_HEADERS: /* trailers, ignore but disallow succeeding DATA or HEADERS frame */
        stream->recvbuf.handle_input = handle_input_post_trailers;
        return 0;
    case H2O_HTTP3_FRAME_TYPE_DATA:
        if (stream->req.content_length != SIZE_MAX &&
            stream->req.content_length - stream->req.req_body_bytes_received < frame.length) {
            if (!quicly_recvstate_transfer_complete(&stream->quic->recvstate))
                quicly_request_stop(stream->quic, H2O_HTTP3_ERROR_EARLY_RESPONSE); /* FIXME numberspace */
            /* Because we might have already called h2o_process_request, the only "consistent" behavior in this case would be to
             * reset the stream. */
            if (!quicly_sendstate_is_open(&stream->quic->sendstate))
                quicly_reset_stream(stream->quic, H2O_HTTP3_ERROR_GENERAL_PROTOCOL);
            set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
            return 0;
        }
        break;
    default:
        return 0;
    }

    /* got a DATA frame */
    if (frame.length != 0) {
        stream->recvbuf.handle_input = handle_input_expect_data_payload;
        stream->recvbuf.bytes_left_in_data_frame = frame.length;
    }

    return 0;
}