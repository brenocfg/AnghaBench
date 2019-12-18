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
struct TYPE_11__ {TYPE_4__* ctx; } ;
struct TYPE_9__ {scalar_t__ sent; scalar_t__ permitted; } ;
struct TYPE_10__ {TYPE_1__ max_data; } ;
struct TYPE_13__ {TYPE_3__ super; TYPE_2__ egress; int /*<<< orphan*/ * application; } ;
typedef  TYPE_5__ quicly_conn_t ;
struct TYPE_14__ {int (* can_send ) (TYPE_6__*,TYPE_5__*,int) ;} ;
struct TYPE_12__ {TYPE_6__* stream_scheduler; } ;

/* Variables and functions */
 int stub1 (TYPE_6__*,TYPE_5__*,int) ; 

__attribute__((used)) static int scheduler_can_send(quicly_conn_t *conn)
{
    /* scheduler would never have data to send, until application keys become available */
    if (conn->application == NULL)
        return 0;
    int conn_is_saturated = !(conn->egress.max_data.sent < conn->egress.max_data.permitted);
    return conn->super.ctx->stream_scheduler->can_send(conn->super.ctx->stream_scheduler, conn, conn_is_saturated);
}