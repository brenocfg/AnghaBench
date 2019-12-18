#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ at; } ;
struct TYPE_18__ {scalar_t__ alarm_at; } ;
struct TYPE_19__ {scalar_t__ send_ack_at; TYPE_6__ loss; } ;
struct TYPE_15__ {int /*<<< orphan*/  validated; } ;
struct TYPE_16__ {TYPE_3__ address_validation; } ;
struct TYPE_17__ {TYPE_4__ peer; } ;
struct TYPE_13__ {int /*<<< orphan*/  control; } ;
struct TYPE_14__ {scalar_t__ flows; TYPE_1__ streams; } ;
struct TYPE_21__ {TYPE_8__ idle_timeout; TYPE_7__ egress; TYPE_5__ super; TYPE_2__ pending; } ;
typedef  TYPE_9__ quicly_conn_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ calc_send_window (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ quicly_linklist_is_linked (int /*<<< orphan*/ *) ; 
 scalar_t__ scheduler_can_send (TYPE_9__*) ; 

int64_t quicly_get_first_timeout(quicly_conn_t *conn)
{
    if (calc_send_window(conn, 0, 0) > 0) {
        if (conn->pending.flows != 0)
            return 0;
        if (quicly_linklist_is_linked(&conn->pending.streams.control))
            return 0;
        if (scheduler_can_send(conn))
            return 0;
    } else if (!conn->super.peer.address_validation.validated) {
        return conn->idle_timeout.at;
    }

    int64_t at = conn->egress.loss.alarm_at;
    if (conn->egress.send_ack_at < at)
        at = conn->egress.send_ack_at;
    if (conn->idle_timeout.at < at)
        at = conn->idle_timeout.at;

    return at;
}