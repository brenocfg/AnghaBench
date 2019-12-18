#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct st_quicly_handle_payload_state_t {int /*<<< orphan*/  end; int /*<<< orphan*/  src; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_stream_data_sender; } ;
struct TYPE_9__ {TYPE_1__ _send_aux; } ;
typedef  TYPE_2__ quicly_stream_t ;
struct TYPE_10__ {int /*<<< orphan*/  stream_id; int /*<<< orphan*/  offset; } ;
typedef  TYPE_3__ quicly_stream_data_blocked_frame_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QUICLY_TRANSPORT_ERROR_FRAME_ENCODING ; 
 int /*<<< orphan*/  STREAM_DATA_BLOCKED_RECEIVE ; 
 int /*<<< orphan*/  probe_now () ; 
 int quicly_decode_stream_data_blocked_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_is_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_request_transmit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_stream_has_receive_side (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_stream_control (TYPE_2__*) ; 
 scalar_t__ should_send_max_stream_data (TYPE_2__*) ; 

__attribute__((used)) static int handle_stream_data_blocked_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    quicly_stream_data_blocked_frame_t frame;
    quicly_stream_t *stream;
    int ret;

    if ((ret = quicly_decode_stream_data_blocked_frame(&state->src, state->end, &frame)) != 0)
        return ret;

    QUICLY_PROBE(STREAM_DATA_BLOCKED_RECEIVE, conn, probe_now(), frame.stream_id, frame.offset);

    if (!quicly_stream_has_receive_side(quicly_is_client(conn), frame.stream_id))
        return QUICLY_TRANSPORT_ERROR_FRAME_ENCODING;

    if ((stream = quicly_get_stream(conn, frame.stream_id)) != NULL) {
        quicly_maxsender_request_transmit(&stream->_send_aux.max_stream_data_sender);
        if (should_send_max_stream_data(stream))
            sched_stream_control(stream);
    }

    return 0;
}