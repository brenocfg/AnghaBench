#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {TYPE_4__* ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  bytes_consumed; int /*<<< orphan*/  sender; } ;
struct TYPE_9__ {TYPE_1__ max_data; } ;
struct TYPE_13__ {TYPE_5__ super; TYPE_2__ ingress; } ;
typedef  TYPE_6__ quicly_conn_t ;
struct TYPE_10__ {scalar_t__ max_data; } ;
struct TYPE_11__ {TYPE_3__ transport_params; } ;

/* Variables and functions */
 int quicly_maxsender_should_send_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int should_send_max_data(quicly_conn_t *conn)
{
    return quicly_maxsender_should_send_max(&conn->ingress.max_data.sender, conn->ingress.max_data.bytes_consumed,
                                            (uint32_t)conn->super.ctx->transport_params.max_data, 512);
}