#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int quicly_sentmap_event_t ;
struct TYPE_9__ {int /*<<< orphan*/  args; scalar_t__ uni; } ;
struct TYPE_10__ {TYPE_1__ max_streams; } ;
struct TYPE_13__ {TYPE_2__ data; } ;
typedef  TYPE_5__ quicly_sent_t ;
typedef  int /*<<< orphan*/  quicly_sent_packet_t ;
typedef  int /*<<< orphan*/  quicly_maxsender_t ;
struct TYPE_11__ {int /*<<< orphan*/ * bidi; int /*<<< orphan*/ * uni; } ;
struct TYPE_12__ {TYPE_3__ max_streams; } ;
struct TYPE_14__ {TYPE_4__ ingress; } ;
typedef  TYPE_6__ quicly_conn_t ;

/* Variables and functions */
#define  QUICLY_SENTMAP_EVENT_ACKED 129 
#define  QUICLY_SENTMAP_EVENT_LOST 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_maxsender_acked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_lost (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_ack_max_streams(quicly_conn_t *conn, const quicly_sent_packet_t *packet, quicly_sent_t *sent,
                              quicly_sentmap_event_t event)
{
    quicly_maxsender_t *maxsender = sent->data.max_streams.uni ? conn->ingress.max_streams.uni : conn->ingress.max_streams.bidi;
    assert(maxsender != NULL); /* we would only receive an ACK if we have sent the frame */

    switch (event) {
    case QUICLY_SENTMAP_EVENT_ACKED:
        quicly_maxsender_acked(maxsender, &sent->data.max_streams.args);
        break;
    case QUICLY_SENTMAP_EVENT_LOST:
        quicly_maxsender_lost(maxsender, &sent->data.max_streams.args);
        break;
    default:
        break;
    }

    return 0;
}