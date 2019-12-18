#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_hwassist; int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_11__ {scalar_t__ qla_watchdog_pause; scalar_t__ stop_rcv; } ;
struct TYPE_10__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_12__ {TYPE_2__ flags; struct ifnet* ifp; TYPE_1__ hw; } ;
typedef  TYPE_3__ qla_host_t ;

/* Variables and functions */
 int CSUM_TCP ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qla_alloc_rcv_bufs (TYPE_3__*) ; 
 scalar_t__ qla_alloc_xmt_bufs (TYPE_3__*) ; 
 scalar_t__ qla_config_lro (TYPE_3__*) ; 
 scalar_t__ qla_init_hw_if (TYPE_3__*) ; 
 int /*<<< orphan*/  qla_stop (TYPE_3__*) ; 

__attribute__((used)) static void
qla_init_locked(qla_host_t *ha)
{
	struct ifnet *ifp = ha->ifp;

	qla_stop(ha);

	if (qla_alloc_xmt_bufs(ha) != 0) 
		return;

	if (qla_alloc_rcv_bufs(ha) != 0)
		return;

	if (qla_config_lro(ha))
		return;

	bcopy(IF_LLADDR(ha->ifp), ha->hw.mac_addr, ETHER_ADDR_LEN);

	ifp->if_hwassist = CSUM_TCP | CSUM_UDP | CSUM_TSO;

	ha->flags.stop_rcv = 0;
	if (qla_init_hw_if(ha) == 0) {
		ifp = ha->ifp;
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		ha->flags.qla_watchdog_pause = 0;
	}

	return;
}