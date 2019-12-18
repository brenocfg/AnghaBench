#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ sender_state; } ;
struct TYPE_23__ {TYPE_4__ rst; } ;
struct TYPE_24__ {TYPE_5__ _send_aux; int /*<<< orphan*/  sendstate; TYPE_1__* callbacks; } ;
typedef  TYPE_6__ quicly_stream_t ;
typedef  scalar_t__ quicly_sentmap_event_t ;
struct TYPE_18__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_20__ {TYPE_12__ args; int /*<<< orphan*/  stream_id; } ;
struct TYPE_21__ {TYPE_2__ stream; } ;
struct TYPE_25__ {TYPE_3__ data; } ;
typedef  TYPE_7__ quicly_sent_t ;
struct TYPE_26__ {scalar_t__ bytes_in_flight; } ;
typedef  TYPE_8__ quicly_sent_packet_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_19__ {int /*<<< orphan*/  (* on_send_shift ) (TYPE_6__*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ QUICLY_SENDER_STATE_NONE ; 
 scalar_t__ QUICLY_SENTMAP_EVENT_ACKED ; 
 scalar_t__ QUICLY_SENTMAP_EVENT_EXPIRED ; 
 int /*<<< orphan*/  STREAM_ACKED ; 
 int /*<<< orphan*/  STREAM_LOST ; 
 int /*<<< orphan*/  destroy_stream (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_now () ; 
 TYPE_6__* quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int quicly_sendstate_acked (int /*<<< orphan*/ *,TYPE_12__*,int,size_t*) ; 
 int quicly_sendstate_lost (int /*<<< orphan*/ *,TYPE_12__*) ; 
 int /*<<< orphan*/  resched_stream_data (TYPE_6__*) ; 
 scalar_t__ stream_is_destroyable (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,size_t) ; 

__attribute__((used)) static int on_ack_stream(quicly_conn_t *conn, const quicly_sent_packet_t *packet, quicly_sent_t *sent, quicly_sentmap_event_t event)
{
    quicly_stream_t *stream;
    int ret;

    if (event == QUICLY_SENTMAP_EVENT_EXPIRED)
        return 0;

    if (event == QUICLY_SENTMAP_EVENT_ACKED) {
        QUICLY_PROBE(STREAM_ACKED, conn, probe_now(), sent->data.stream.stream_id, sent->data.stream.args.start,
                     sent->data.stream.args.end - sent->data.stream.args.start);
    } else {
        QUICLY_PROBE(STREAM_LOST, conn, probe_now(), sent->data.stream.stream_id, sent->data.stream.args.start,
                     sent->data.stream.args.end - sent->data.stream.args.start);
    }

    /* TODO cache pointer to stream (using a generation counter?) */
    if ((stream = quicly_get_stream(conn, sent->data.stream.stream_id)) == NULL)
        return 0;

    if (event == QUICLY_SENTMAP_EVENT_ACKED) {
        size_t bytes_to_shift;
        if ((ret = quicly_sendstate_acked(&stream->sendstate, &sent->data.stream.args, packet->bytes_in_flight != 0,
                                          &bytes_to_shift)) != 0)
            return ret;
        if (stream_is_destroyable(stream)) {
            destroy_stream(stream, 0);
        } else if (bytes_to_shift != 0) {
            stream->callbacks->on_send_shift(stream, bytes_to_shift);
        }
    } else {
        /* FIXME handle rto error */
        if ((ret = quicly_sendstate_lost(&stream->sendstate, &sent->data.stream.args)) != 0)
            return ret;
        if (stream->_send_aux.rst.sender_state == QUICLY_SENDER_STATE_NONE)
            resched_stream_data(stream);
    }

    return 0;
}