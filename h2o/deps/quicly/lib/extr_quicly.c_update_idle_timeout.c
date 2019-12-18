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
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_21__ {int should_rearm_on_send; scalar_t__ at; } ;
struct TYPE_19__ {TYPE_6__* conf; int /*<<< orphan*/  rtt; } ;
struct TYPE_20__ {TYPE_7__ loss; } ;
struct TYPE_13__ {scalar_t__ idle_timeout; } ;
struct TYPE_14__ {TYPE_1__ transport_params; } ;
struct TYPE_17__ {TYPE_4__* ctx; TYPE_2__ peer; } ;
struct TYPE_12__ {TYPE_9__ idle_timeout; TYPE_8__ egress; TYPE_5__ super; int /*<<< orphan*/ * handshake; int /*<<< orphan*/ * initial; } ;
typedef  TYPE_10__ quicly_conn_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_18__ {int /*<<< orphan*/  min_pto; } ;
struct TYPE_15__ {scalar_t__ idle_timeout; int /*<<< orphan*/  max_ack_delay; } ;
struct TYPE_16__ {TYPE_3__ transport_params; } ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ now ; 
 int quicly_rtt_get_pto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_idle_timeout(quicly_conn_t *conn, int is_in_receive)
{
    if (!is_in_receive && !conn->idle_timeout.should_rearm_on_send)
        return;

    int64_t idle_msec = INT64_MAX;
    /* TODO reconsider how to refer to peer's idle-timeout value after https://github.com/quicwg/base-drafts/issues/2602 gets
     * resolved */
    if (conn->initial == NULL && conn->handshake == NULL && conn->super.peer.transport_params.idle_timeout != 0)
        idle_msec = conn->super.peer.transport_params.idle_timeout;
    if (conn->super.ctx->transport_params.idle_timeout != 0 && conn->super.ctx->transport_params.idle_timeout < idle_msec)
        idle_msec = conn->super.ctx->transport_params.idle_timeout;

    if (idle_msec == INT64_MAX)
        return;

    uint32_t three_pto = 3 * quicly_rtt_get_pto(&conn->egress.loss.rtt, conn->super.ctx->transport_params.max_ack_delay,
                                                conn->egress.loss.conf->min_pto);
    conn->idle_timeout.at = now + (idle_msec > three_pto ? idle_msec : three_pto);
    conn->idle_timeout.should_rearm_on_send = is_in_receive;
}