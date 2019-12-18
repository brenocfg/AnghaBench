#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  flows; } ;
struct TYPE_8__ {int /*<<< orphan*/  generation; } ;
struct TYPE_9__ {TYPE_2__ new_token; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_11__ {TYPE_4__ pending; TYPE_3__ egress; TYPE_1__ super; } ;
typedef  TYPE_5__ quicly_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_PENDING_FLOW_NEW_TOKEN_BIT ; 
 scalar_t__ QUICLY_STATE_CONNECTED ; 

int quicly_send_resumption_token(quicly_conn_t *conn)
{
    if (conn->super.state <= QUICLY_STATE_CONNECTED) {
        ++conn->egress.new_token.generation;
        conn->pending.flows |= QUICLY_PENDING_FLOW_NEW_TOKEN_BIT;
    }
    return 0;
}