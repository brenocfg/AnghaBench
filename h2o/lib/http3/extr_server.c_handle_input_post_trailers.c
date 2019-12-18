#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_http3_server_stream_t {TYPE_2__* quic; } ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ h2o_http3_read_frame_t ;
struct TYPE_6__ {int /*<<< orphan*/  sendstate; int /*<<< orphan*/  recvstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HTTP3_ERROR_FRAME_UNEXPECTED ; 
#define  H2O_HTTP3_FRAME_TYPE_DATA 130 
#define  H2O_HTTP3_FRAME_TYPE_HEADERS 129 
#define  H2O_HTTP3_FRAME_TYPE_PRIORITY 128 
 int /*<<< orphan*/  H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT ; 
 int /*<<< orphan*/  H2O_HTTP3_STREAM_TYPE_REQUEST ; 
 int h2o_http3_read_frame (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  quicly_recvstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_request_stop (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_reset_stream (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendstate_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_state (struct st_h2o_http3_server_stream_t*,int /*<<< orphan*/ ) ; 

int handle_input_post_trailers(struct st_h2o_http3_server_stream_t *stream, const uint8_t **src, const uint8_t *src_end,
                               const char **err_desc)
{
    h2o_http3_read_frame_t frame;
    int ret;

    /* read and ignore unknown frames */
    if ((ret = h2o_http3_read_frame(&frame, 0, H2O_HTTP3_STREAM_TYPE_REQUEST, src, src_end, err_desc)) != 0)
        return ret;
    switch (frame.type) {
    case H2O_HTTP3_FRAME_TYPE_PRIORITY:
    case H2O_HTTP3_FRAME_TYPE_HEADERS:
    case H2O_HTTP3_FRAME_TYPE_DATA:
        if (!quicly_recvstate_transfer_complete(&stream->quic->recvstate))
            quicly_request_stop(stream->quic, H2O_HTTP3_ERROR_FRAME_UNEXPECTED);
        if (quicly_sendstate_is_open(&stream->quic->sendstate))
            quicly_reset_stream(stream->quic, H2O_HTTP3_ERROR_FRAME_UNEXPECTED);
        set_state(stream, H2O_HTTP3_SERVER_STREAM_STATE_CLOSE_WAIT);
        return 0;
    default:
        break;
    }

    return 0;
}