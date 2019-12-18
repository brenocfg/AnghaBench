#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* rx_cntxt_rsp; } ;
struct TYPE_10__ {TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  cntxt_id; } ;
struct TYPE_8__ {TYPE_1__ rx_rsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q8_MAC_RCV_ENABLE_PROMISCUOUS ; 
 int /*<<< orphan*/  qla_set_mac_rcv_mode (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qla_set_promisc(qla_host_t *ha)
{
	(void)qla_set_mac_rcv_mode(ha,
		(ha->hw.rx_cntxt_rsp)->rx_rsp.cntxt_id,
		Q8_MAC_RCV_ENABLE_PROMISCUOUS);
}