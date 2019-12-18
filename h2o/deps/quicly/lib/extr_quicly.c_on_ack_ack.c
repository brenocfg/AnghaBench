#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ num_ranges; } ;
struct st_quicly_pn_space_t {scalar_t__ unacked_count; int /*<<< orphan*/  largest_pn_received_at; TYPE_10__ ack_queue; } ;
typedef  scalar_t__ quicly_sentmap_event_t ;
struct TYPE_18__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_19__ {TYPE_4__ range; } ;
struct TYPE_20__ {TYPE_5__ ack; } ;
struct TYPE_21__ {TYPE_6__ data; } ;
typedef  TYPE_7__ quicly_sent_t ;
struct TYPE_22__ {int ack_epoch; } ;
typedef  TYPE_8__ quicly_sent_packet_t ;
struct TYPE_23__ {TYPE_3__* application; TYPE_2__* handshake; TYPE_1__* initial; } ;
typedef  TYPE_9__ quicly_conn_t ;
struct TYPE_17__ {struct st_quicly_pn_space_t super; } ;
struct TYPE_16__ {struct st_quicly_pn_space_t super; } ;
struct TYPE_15__ {struct st_quicly_pn_space_t super; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
#define  QUICLY_EPOCH_1RTT 130 
#define  QUICLY_EPOCH_HANDSHAKE 129 
#define  QUICLY_EPOCH_INITIAL 128 
 scalar_t__ QUICLY_SENTMAP_EVENT_ACKED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  quicly_ranges_subtract (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_ack_ack(quicly_conn_t *conn, const quicly_sent_packet_t *packet, quicly_sent_t *sent, quicly_sentmap_event_t event)
{
    /* TODO log */

    if (event == QUICLY_SENTMAP_EVENT_ACKED) {
        /* find the pn space */
        struct st_quicly_pn_space_t *space;
        switch (packet->ack_epoch) {
        case QUICLY_EPOCH_INITIAL:
            space = &conn->initial->super;
            break;
        case QUICLY_EPOCH_HANDSHAKE:
            space = &conn->handshake->super;
            break;
        case QUICLY_EPOCH_1RTT:
            space = &conn->application->super;
            break;
        default:
            assert(!"FIXME");
        }
        if (space != NULL) {
            quicly_ranges_subtract(&space->ack_queue, sent->data.ack.range.start, sent->data.ack.range.end);
            if (space->ack_queue.num_ranges == 0) {
                space->largest_pn_received_at = INT64_MAX;
                space->unacked_count = 0;
            }
        }
    }

    return 0;
}