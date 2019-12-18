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
struct TYPE_12__ {int /*<<< orphan*/  max_streams_bidi; int /*<<< orphan*/  max_streams_uni; int /*<<< orphan*/  max_data; } ;
struct TYPE_13__ {TYPE_4__ transport_params; } ;
struct TYPE_14__ {TYPE_5__ peer; } ;
struct TYPE_9__ {int /*<<< orphan*/  bidi; int /*<<< orphan*/  uni; } ;
struct TYPE_10__ {int /*<<< orphan*/  permitted; } ;
struct TYPE_11__ {TYPE_1__ max_streams; TYPE_2__ max_data; } ;
struct TYPE_15__ {TYPE_6__ super; TYPE_3__ egress; } ;
typedef  TYPE_7__ quicly_conn_t ;

/* Variables and functions */
 int update_max_streams (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_peer_transport_params(quicly_conn_t *conn)
{
    int ret;

    conn->egress.max_data.permitted = conn->super.peer.transport_params.max_data;
    if ((ret = update_max_streams(&conn->egress.max_streams.uni, conn->super.peer.transport_params.max_streams_uni)) != 0)
        return ret;
    if ((ret = update_max_streams(&conn->egress.max_streams.bidi, conn->super.peer.transport_params.max_streams_bidi)) != 0)
        return ret;

    return 0;
}