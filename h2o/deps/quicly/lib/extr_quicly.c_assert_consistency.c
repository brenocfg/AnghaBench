#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ alarm_at; scalar_t__ loss_time; } ;
struct TYPE_10__ {scalar_t__ bytes_in_flight; } ;
struct TYPE_12__ {TYPE_3__ loss; TYPE_2__ sentmap; } ;
struct TYPE_14__ {scalar_t__ validated; } ;
struct TYPE_13__ {TYPE_6__ address_validation; } ;
struct TYPE_9__ {TYPE_5__ peer; } ;
struct TYPE_15__ {TYPE_4__ egress; TYPE_1__ super; } ;
typedef  TYPE_7__ quicly_conn_t ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ now ; 

__attribute__((used)) static void assert_consistency(quicly_conn_t *conn, int timer_must_be_in_future)
{
    if (conn->egress.sentmap.bytes_in_flight != 0) {
        assert(conn->egress.loss.alarm_at != INT64_MAX);
    } else {
        assert(conn->egress.loss.loss_time == INT64_MAX);
    }
    /* Allow timers not in the future when the peer is not yet validated, since we may not be able to send packets even when timers
     * fire. */
    if (timer_must_be_in_future && conn->super.peer.address_validation.validated)
        assert(now < conn->egress.loss.alarm_at);
}