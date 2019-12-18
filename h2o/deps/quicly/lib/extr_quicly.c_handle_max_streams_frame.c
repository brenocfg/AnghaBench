#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct st_quicly_handle_payload_state_t {scalar_t__ frame_type; int /*<<< orphan*/  end; int /*<<< orphan*/  src; } ;
struct TYPE_11__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_3__ quicly_max_streams_frame_t ;
struct TYPE_9__ {int /*<<< orphan*/  bidi; int /*<<< orphan*/  uni; } ;
struct TYPE_10__ {TYPE_1__ max_streams; } ;
struct TYPE_12__ {TYPE_2__ egress; } ;
typedef  TYPE_4__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_STREAMS_RECEIVE ; 
 scalar_t__ QUICLY_FRAME_TYPE_MAX_STREAMS_UNI ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open_blocked_streams (TYPE_4__*,int) ; 
 int /*<<< orphan*/  probe_now () ; 
 int quicly_decode_max_streams_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int update_max_streams (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_max_streams_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    quicly_max_streams_frame_t frame;
    int uni = state->frame_type == QUICLY_FRAME_TYPE_MAX_STREAMS_UNI, ret;

    if ((ret = quicly_decode_max_streams_frame(&state->src, state->end, &frame)) != 0)
        return ret;

    QUICLY_PROBE(MAX_STREAMS_RECEIVE, conn, probe_now(), frame.count, uni);

    if ((ret = update_max_streams(uni ? &conn->egress.max_streams.uni : &conn->egress.max_streams.bidi, frame.count)) != 0)
        return ret;

    open_blocked_streams(conn, uni);

    return 0;
}