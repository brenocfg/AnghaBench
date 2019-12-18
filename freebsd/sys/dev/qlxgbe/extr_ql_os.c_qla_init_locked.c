#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_hwassist; int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_11__ {int sp_log_stop_events; int sp_log_stop; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_12__ {int qla_interface_up; scalar_t__ qla_watchdog_pause; TYPE_1__ hw; scalar_t__ tx_tso_frames; scalar_t__ hw_vlan_tx_frames; struct ifnet* ifp; scalar_t__ stop_rcv; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int Q8_SP_LOG_STOP_IF_START_FAILURE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_init_hw_if (TYPE_2__*) ; 
 int /*<<< orphan*/  ql_sp_log (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_update_link_state (TYPE_2__*) ; 
 scalar_t__ qla_alloc_rcv_bufs (TYPE_2__*) ; 
 scalar_t__ qla_alloc_xmt_bufs (TYPE_2__*) ; 
 int /*<<< orphan*/  qla_confirm_9kb_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  qla_stop (TYPE_2__*) ; 

__attribute__((used)) static void
qla_init_locked(qla_host_t *ha)
{
	struct ifnet *ifp = ha->ifp;

	ql_sp_log(ha, 14, 0, 0, 0, 0, 0, 0);

	qla_stop(ha);

	if (qla_alloc_xmt_bufs(ha) != 0) 
		return;

	qla_confirm_9kb_enable(ha);

	if (qla_alloc_rcv_bufs(ha) != 0)
		return;

	bcopy(IF_LLADDR(ha->ifp), ha->hw.mac_addr, ETHER_ADDR_LEN);

	ifp->if_hwassist = CSUM_TCP | CSUM_UDP | CSUM_TSO;
	ifp->if_hwassist |= CSUM_TCP_IPV6 | CSUM_UDP_IPV6;

	ha->stop_rcv = 0;
 	if (ql_init_hw_if(ha) == 0) {
		ifp = ha->ifp;
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		ha->hw_vlan_tx_frames = 0;
		ha->tx_tso_frames = 0;
		ha->qla_interface_up = 1;
		ql_update_link_state(ha);
	} else {
		if (ha->hw.sp_log_stop_events & Q8_SP_LOG_STOP_IF_START_FAILURE)
			ha->hw.sp_log_stop = -1;
	}

	ha->qla_watchdog_pause = 0;

	return;
}