#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int link_up; } ;
struct TYPE_8__ {TYPE_1__ flags; } ;
struct TYPE_9__ {scalar_t__ pci_func; TYPE_5__* ifp; TYPE_2__ hw; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_10__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  Q8_LINK_STATE ; 
 int READ_REG32 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_link_state_change (TYPE_5__*,int /*<<< orphan*/ ) ; 

void
qla_update_link_state(qla_host_t *ha)
{
	uint32_t link_state;
	uint32_t prev_link_state;

	if (!(ha->ifp->if_drv_flags & IFF_DRV_RUNNING)) {
		ha->hw.flags.link_up = 0;
		return;
	}
	link_state = READ_REG32(ha, Q8_LINK_STATE);

	prev_link_state =  ha->hw.flags.link_up;

	if (ha->pci_func == 0)
		ha->hw.flags.link_up = (((link_state & 0xF) == 1)? 1 : 0);
	else
		ha->hw.flags.link_up = ((((link_state >> 4)& 0xF) == 1)? 1 : 0);

	if (prev_link_state !=  ha->hw.flags.link_up) {
		if (ha->hw.flags.link_up) {
			if_link_state_change(ha->ifp, LINK_STATE_UP);
		} else {
			if_link_state_change(ha->ifp, LINK_STATE_DOWN);
		}
	}
}