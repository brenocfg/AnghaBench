#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  sent; } ;
struct TYPE_10__ {scalar_t__ bytes_in_flight; } ;
struct TYPE_14__ {TYPE_6__ max_data; TYPE_1__ sentmap; int /*<<< orphan*/  last_retransmittable_sent_at; int /*<<< orphan*/  loss; } ;
struct TYPE_11__ {scalar_t__ send_probe; } ;
struct TYPE_12__ {TYPE_2__ address_validation; } ;
struct TYPE_13__ {TYPE_3__ peer; } ;
struct TYPE_16__ {TYPE_5__ egress; TYPE_4__ super; } ;
typedef  TYPE_7__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  quicly_loss_update_alarm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduler_can_send (TYPE_7__*) ; 

__attribute__((used)) static void update_loss_alarm(quicly_conn_t *conn)
{
    quicly_loss_update_alarm(&conn->egress.loss, now, conn->egress.last_retransmittable_sent_at,
                             conn->egress.sentmap.bytes_in_flight != 0 || conn->super.peer.address_validation.send_probe,
                             scheduler_can_send(conn), conn->egress.max_data.sent);
}