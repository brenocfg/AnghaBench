#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct st_quicly_handle_payload_state_t {scalar_t__ frame_type; int /*<<< orphan*/  end; int /*<<< orphan*/  src; } ;
struct TYPE_13__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_4__ quicly_streams_blocked_frame_t ;
typedef  int /*<<< orphan*/  quicly_maxsender_t ;
struct TYPE_12__ {scalar_t__ send_ack_at; } ;
struct TYPE_10__ {int /*<<< orphan*/ * bidi; int /*<<< orphan*/ * uni; } ;
struct TYPE_11__ {TYPE_1__ max_streams; } ;
struct TYPE_14__ {TYPE_3__ egress; TYPE_2__ ingress; } ;
typedef  TYPE_5__ quicly_conn_t ;

/* Variables and functions */
 scalar_t__ QUICLY_FRAME_TYPE_STREAMS_BLOCKED_UNI ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STREAMS_BLOCKED_RECEIVE ; 
 int /*<<< orphan*/  probe_now () ; 
 int quicly_decode_streams_blocked_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  quicly_maxsender_request_transmit (int /*<<< orphan*/ *) ; 
 scalar_t__ should_send_max_streams (TYPE_5__*,int) ; 

__attribute__((used)) static int handle_streams_blocked_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    quicly_streams_blocked_frame_t frame;
    int uni = state->frame_type == QUICLY_FRAME_TYPE_STREAMS_BLOCKED_UNI, ret;

    if ((ret = quicly_decode_streams_blocked_frame(&state->src, state->end, &frame)) != 0)
        return ret;

    QUICLY_PROBE(STREAMS_BLOCKED_RECEIVE, conn, probe_now(), frame.count, uni);

    quicly_maxsender_t *maxsender = uni ? conn->ingress.max_streams.uni : conn->ingress.max_streams.bidi;
    if (maxsender != NULL) {
        quicly_maxsender_request_transmit(maxsender);
        if (should_send_max_streams(conn, uni))
            conn->egress.send_ack_at = 0;
    }

    return 0;
}