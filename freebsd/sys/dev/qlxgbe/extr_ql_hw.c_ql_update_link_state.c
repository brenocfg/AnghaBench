#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int link_up; } ;
struct TYPE_7__ {scalar_t__ pci_func; TYPE_4__* ifp; TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;
struct TYPE_8__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  Q8_LINK_STATE ; 
 int READ_REG32 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_rel_8 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
ql_update_link_state(qla_host_t *ha)
{
	uint32_t link_state = 0;
	uint32_t prev_link_state;

	prev_link_state =  ha->hw.link_up;

	if (ha->ifp->if_drv_flags & IFF_DRV_RUNNING) {
		link_state = READ_REG32(ha, Q8_LINK_STATE);

		if (ha->pci_func == 0) {
			link_state = (((link_state & 0xF) == 1)? 1 : 0);
		} else {
			link_state = ((((link_state >> 4)& 0xF) == 1)? 1 : 0);
		}
	}

	atomic_store_rel_8(&ha->hw.link_up, (uint8_t)link_state);

	if (prev_link_state !=  ha->hw.link_up) {
		if (ha->hw.link_up) {
			if_link_state_change(ha->ifp, LINK_STATE_UP);
		} else {
			if_link_state_change(ha->ifp, LINK_STATE_DOWN);
		}
	}
	return;
}