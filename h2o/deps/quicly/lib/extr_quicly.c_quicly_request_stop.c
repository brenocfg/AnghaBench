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
struct TYPE_9__ {scalar_t__ sender_state; int /*<<< orphan*/  error_code; } ;
struct TYPE_8__ {TYPE_3__ stop_sending; } ;
struct TYPE_7__ {scalar_t__ eos; } ;
struct TYPE_10__ {TYPE_2__ _send_aux; TYPE_1__ recvstate; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  conn; } ;
typedef  TYPE_4__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_ERROR_GET_ERROR_CODE (int) ; 
 int /*<<< orphan*/  QUICLY_ERROR_IS_QUIC_APPLICATION (int) ; 
 scalar_t__ QUICLY_SENDER_STATE_NONE ; 
 scalar_t__ QUICLY_SENDER_STATE_SEND ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_is_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_stream_has_receive_side (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_stream_control (TYPE_4__*) ; 

void quicly_request_stop(quicly_stream_t *stream, int err)
{
    assert(quicly_stream_has_receive_side(quicly_is_client(stream->conn), stream->stream_id));
    assert(QUICLY_ERROR_IS_QUIC_APPLICATION(err));

    /* send STOP_SENDING if the incoming side of the stream is still open */
    if (stream->recvstate.eos == UINT64_MAX && stream->_send_aux.stop_sending.sender_state == QUICLY_SENDER_STATE_NONE) {
        stream->_send_aux.stop_sending.sender_state = QUICLY_SENDER_STATE_SEND;
        stream->_send_aux.stop_sending.error_code = QUICLY_ERROR_GET_ERROR_CODE(err);
        sched_stream_control(stream);
    }
}