#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cc; int /*<<< orphan*/  rtt; } ;
typedef  TYPE_4__ quicly_stats_t ;
struct TYPE_10__ {int /*<<< orphan*/  rtt; } ;
struct TYPE_11__ {int /*<<< orphan*/  cc; TYPE_2__ loss; } ;
struct TYPE_9__ {int /*<<< orphan*/  stats; } ;
struct TYPE_13__ {TYPE_3__ egress; TYPE_1__ super; } ;
typedef  TYPE_5__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

int quicly_get_stats(quicly_conn_t *conn, quicly_stats_t *stats)
{
    /* copy the pre-built stats fields */
    memcpy(stats, &conn->super.stats, sizeof(conn->super.stats));

    /* set or generate the non-pre-built stats fields here */
    stats->rtt = conn->egress.loss.rtt;
    stats->cc = conn->egress.cc;

    return 0;
}