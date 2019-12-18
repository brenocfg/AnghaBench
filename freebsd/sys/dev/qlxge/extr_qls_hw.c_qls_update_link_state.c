#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int link_up; int pci_func; TYPE_3__* ifp; } ;
typedef  TYPE_1__ qla_host_t ;
struct TYPE_6__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  Q81_CTL_STATUS ; 
 int Q81_CTL_STATUS_PL0 ; 
 int Q81_CTL_STATUS_PL1 ; 
 int READ_REG32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_3__*,int /*<<< orphan*/ ) ; 

void
qls_update_link_state(qla_host_t *ha)
{
	uint32_t link_state;
	uint32_t prev_link_state;

	if (!(ha->ifp->if_drv_flags & IFF_DRV_RUNNING)) {
		ha->link_up = 0;
		return;
	}
	link_state = READ_REG32(ha, Q81_CTL_STATUS);

	prev_link_state =  ha->link_up;

	if ((ha->pci_func & 0x1) == 0)
		ha->link_up = ((link_state & Q81_CTL_STATUS_PL0)? 1 : 0);
	else
		ha->link_up = ((link_state & Q81_CTL_STATUS_PL1)? 1 : 0);

	if (prev_link_state !=  ha->link_up) {


		if (ha->link_up) {
			if_link_state_change(ha->ifp, LINK_STATE_UP);
		} else {
			if_link_state_change(ha->ifp, LINK_STATE_DOWN);
		}
	}
	return;
}