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
typedef  int /*<<< orphan*/  quicly_sentmap_iter_t ;
struct TYPE_9__ {scalar_t__ packet_number; unsigned int ack_epoch; } ;
typedef  TYPE_2__ quicly_sent_packet_t ;
struct TYPE_8__ {int /*<<< orphan*/  sentmap; } ;
struct TYPE_10__ {TYPE_1__ egress; } ;
typedef  TYPE_3__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_SENTMAP_EVENT_EXPIRED ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  init_acks_iter (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* quicly_sentmap_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_skip (int /*<<< orphan*/ *) ; 
 int quicly_sentmap_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 

int discard_sentmap_by_epoch(quicly_conn_t *conn, unsigned ack_epochs)
{
    quicly_sentmap_iter_t iter;
    const quicly_sent_packet_t *sent;
    int ret = 0;

    init_acks_iter(conn, &iter);

    while ((sent = quicly_sentmap_get(&iter))->packet_number != UINT64_MAX) {
        if ((ack_epochs & (1u << sent->ack_epoch)) != 0) {
            if ((ret = quicly_sentmap_update(&conn->egress.sentmap, &iter, QUICLY_SENTMAP_EVENT_EXPIRED, conn)) != 0)
                return ret;
        } else {
            quicly_sentmap_skip(&iter);
        }
    }

    return ret;
}