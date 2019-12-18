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
struct TYPE_12__ {scalar_t__ max_ack_delay; } ;
struct TYPE_13__ {TYPE_4__ transport_params; } ;
struct TYPE_14__ {TYPE_5__ peer; } ;
struct TYPE_9__ {int smoothed; int variance; } ;
struct TYPE_10__ {TYPE_1__ rtt; } ;
struct TYPE_11__ {TYPE_2__ loss; } ;
struct TYPE_15__ {TYPE_6__ super; TYPE_3__ egress; } ;
typedef  TYPE_7__ quicly_conn_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ QUICLY_DELAYED_ACK_TIMEOUT ; 

__attribute__((used)) static int64_t get_sentmap_expiration_time(quicly_conn_t *conn)
{
    /* TODO reconsider this (maybe 3 PTO? also not sure why we need to add ack-delay twice) */
    /* TODO (jri): The timeouts used here should be entirely the peer's */
    return (conn->egress.loss.rtt.smoothed + conn->egress.loss.rtt.variance) * 4 + conn->super.peer.transport_params.max_ack_delay +
           QUICLY_DELAYED_ACK_TIMEOUT;
}