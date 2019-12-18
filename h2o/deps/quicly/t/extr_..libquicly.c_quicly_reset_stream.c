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
struct TYPE_7__ {scalar_t__ sender_state; int /*<<< orphan*/  error_code; } ;
struct TYPE_8__ {TYPE_1__ rst; } ;
struct TYPE_9__ {TYPE_2__ _send_aux; int /*<<< orphan*/  sendstate; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  conn; } ;
typedef  TYPE_3__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_ERROR_GET_ERROR_CODE (int) ; 
 int QUICLY_ERROR_IS_QUIC_APPLICATION (int) ; 
 scalar_t__ QUICLY_SENDER_STATE_NONE ; 
 scalar_t__ QUICLY_SENDER_STATE_SEND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  quicly_is_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sendstate_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sendstate_transfer_complete (int /*<<< orphan*/ *) ; 
 int quicly_stream_has_send_side (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resched_stream_data (TYPE_3__*) ; 
 int /*<<< orphan*/  sched_stream_control (TYPE_3__*) ; 

void quicly_reset_stream(quicly_stream_t *stream, int err)
{
    assert(quicly_stream_has_send_side(quicly_is_client(stream->conn), stream->stream_id));
    assert(QUICLY_ERROR_IS_QUIC_APPLICATION(err));
    assert(stream->_send_aux.rst.sender_state == QUICLY_SENDER_STATE_NONE);
    assert(!quicly_sendstate_transfer_complete(&stream->sendstate));

    /* dispose sendbuf state */
    quicly_sendstate_reset(&stream->sendstate);

    /* setup RST_STREAM */
    stream->_send_aux.rst.sender_state = QUICLY_SENDER_STATE_SEND;
    stream->_send_aux.rst.error_code = QUICLY_ERROR_GET_ERROR_CODE(err);

    /* schedule for delivery */
    sched_stream_control(stream);
    resched_stream_data(stream);
}