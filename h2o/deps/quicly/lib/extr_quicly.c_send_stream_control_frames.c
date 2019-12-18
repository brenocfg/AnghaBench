#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_29__ {int /*<<< orphan*/  size_inflight; } ;
struct TYPE_27__ {scalar_t__ sender_state; int /*<<< orphan*/  error_code; } ;
struct TYPE_22__ {scalar_t__ sender_state; int /*<<< orphan*/  error_code; } ;
struct TYPE_28__ {TYPE_6__ rst; int /*<<< orphan*/  max_stream_data_sender; TYPE_1__ stop_sending; } ;
struct TYPE_24__ {scalar_t__ window; } ;
struct TYPE_23__ {scalar_t__ data_off; } ;
struct TYPE_30__ {TYPE_8__ sendstate; TYPE_7__ _send_aux; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  conn; TYPE_3__ _recv_aux; TYPE_2__ recvstate; } ;
typedef  TYPE_9__ quicly_stream_t ;
struct TYPE_25__ {int /*<<< orphan*/  args; int /*<<< orphan*/  stream_id; } ;
struct TYPE_26__ {TYPE_4__ max_stream_data; } ;
struct TYPE_20__ {TYPE_5__ data; } ;
typedef  TYPE_10__ quicly_sent_t ;
struct TYPE_21__ {int /*<<< orphan*/  dst; } ;
typedef  TYPE_11__ quicly_send_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_STREAM_DATA_SEND ; 
 int /*<<< orphan*/  QUICLY_MAX_STREAM_DATA_FRAME_CAPACITY ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  QUICLY_RST_FRAME_CAPACITY ; 
 scalar_t__ QUICLY_SENDER_STATE_SEND ; 
 int /*<<< orphan*/  QUICLY_STOP_SENDING_FRAME_CAPACITY ; 
 int allocate_ack_eliciting_frame (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ,TYPE_10__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_ack_max_stream_data ; 
 int /*<<< orphan*/  on_ack_rst_stream ; 
 int /*<<< orphan*/  on_ack_stop_sending ; 
 int prepare_stream_state_sender (TYPE_9__*,scalar_t__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_now () ; 
 int /*<<< orphan*/  quicly_encode_max_stream_data_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  quicly_encode_rst_stream_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_encode_stop_sending_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_maxsender_record (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ should_send_max_stream_data (TYPE_9__*) ; 

__attribute__((used)) static int send_stream_control_frames(quicly_stream_t *stream, quicly_send_context_t *s)
{
    int ret;

    /* send STOP_SENDING if necessray */
    if (stream->_send_aux.stop_sending.sender_state == QUICLY_SENDER_STATE_SEND) {
        /* FIXME also send an empty STREAM frame */
        if ((ret = prepare_stream_state_sender(stream, &stream->_send_aux.stop_sending.sender_state, s,
                                               QUICLY_STOP_SENDING_FRAME_CAPACITY, on_ack_stop_sending)) != 0)
            return ret;
        s->dst = quicly_encode_stop_sending_frame(s->dst, stream->stream_id, stream->_send_aux.stop_sending.error_code);
    }

    /* send MAX_STREAM_DATA if necessary */
    if (should_send_max_stream_data(stream)) {
        uint64_t new_value = stream->recvstate.data_off + stream->_recv_aux.window;
        quicly_sent_t *sent;
        /* prepare */
        if ((ret = allocate_ack_eliciting_frame(stream->conn, s, QUICLY_MAX_STREAM_DATA_FRAME_CAPACITY, &sent,
                                                on_ack_max_stream_data)) != 0)
            return ret;
        /* send */
        s->dst = quicly_encode_max_stream_data_frame(s->dst, stream->stream_id, new_value);
        /* register ack */
        sent->data.max_stream_data.stream_id = stream->stream_id;
        quicly_maxsender_record(&stream->_send_aux.max_stream_data_sender, new_value, &sent->data.max_stream_data.args);
        QUICLY_PROBE(MAX_STREAM_DATA_SEND, stream->conn, probe_now(), stream, new_value);
    }

    /* send RST_STREAM if necessary */
    if (stream->_send_aux.rst.sender_state == QUICLY_SENDER_STATE_SEND) {
        if ((ret = prepare_stream_state_sender(stream, &stream->_send_aux.rst.sender_state, s, QUICLY_RST_FRAME_CAPACITY,
                                               on_ack_rst_stream)) != 0)
            return ret;
        s->dst = quicly_encode_rst_stream_frame(s->dst, stream->stream_id, stream->_send_aux.rst.error_code,
                                                stream->sendstate.size_inflight);
    }

    return 0;
}