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
struct TYPE_11__ {int /*<<< orphan*/  args; } ;
struct TYPE_12__ {TYPE_3__ max_data; } ;
struct TYPE_13__ {TYPE_4__ data; } ;
typedef  TYPE_5__ quicly_sent_t ;
typedef  int /*<<< orphan*/  quicly_sent_packet_t ;
struct TYPE_9__ {int /*<<< orphan*/  sender; } ;
struct TYPE_10__ {TYPE_1__ max_data; } ;
struct TYPE_14__ {TYPE_2__ ingress; } ;
typedef  TYPE_6__ quicly_conn_t ;

/* Variables and functions */
#define  QUICLY_SENTMAP_EVENT_ACKED 129 
#define  QUICLY_SENTMAP_EVENT_LOST 128 
 int /*<<< orphan*/  quicly_maxsender_acked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_lost (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_ack_max_data(quicly_conn_t *conn, const quicly_sent_packet_t *packet, quicly_sent_t *sent,
                           quicly_sentmap_event_t event)
{
    switch (event) {
    case QUICLY_SENTMAP_EVENT_ACKED:
        quicly_maxsender_acked(&conn->ingress.max_data.sender, &sent->data.max_data.args);
        break;
    case QUICLY_SENTMAP_EVENT_LOST:
        quicly_maxsender_lost(&conn->ingress.max_data.sender, &sent->data.max_data.args);
        break;
    default:
        break;
    }

    return 0;
}