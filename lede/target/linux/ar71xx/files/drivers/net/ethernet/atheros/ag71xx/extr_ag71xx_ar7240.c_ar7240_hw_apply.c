#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct switch_dev {int dummy; } ;
struct TYPE_2__ {int ports; } ;
struct ar7240sw {int* vlan_table; int* vlan_id; TYPE_1__ swdev; scalar_t__ vlan; } ;
typedef  int /*<<< orphan*/  portmask ;

/* Variables and functions */
 int AR7240_MAX_VLANS ; 
 int AR7240_NUM_PORTS ; 
 int AR7240_PORT_CPU ; 
 int AR7240_VTU_OP_FLUSH ; 
 int AR7240_VTU_OP_LOAD ; 
 int AR7240_VTU_VID_S ; 
 int /*<<< orphan*/  ar7240_vtu_op (struct ar7240sw*,int,int) ; 
 int /*<<< orphan*/  ar7240sw_setup_port (struct ar7240sw*,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct ar7240sw* sw_to_ar7240 (struct switch_dev*) ; 

__attribute__((used)) static int
ar7240_hw_apply(struct switch_dev *dev)
{
	struct ar7240sw *as = sw_to_ar7240(dev);
	u8 portmask[AR7240_NUM_PORTS];
	int i, j;

	/* flush all vlan translation unit entries */
	ar7240_vtu_op(as, AR7240_VTU_OP_FLUSH, 0);

	memset(portmask, 0, sizeof(portmask));
	if (as->vlan) {
		/* calculate the port destination masks and load vlans
		 * into the vlan translation unit */
		for (j = 0; j < AR7240_MAX_VLANS; j++) {
			u8 vp = as->vlan_table[j];

			if (!vp)
				continue;

			for (i = 0; i < as->swdev.ports; i++) {
				u8 mask = (1 << i);
				if (vp & mask)
					portmask[i] |= vp & ~mask;
			}

			ar7240_vtu_op(as,
				AR7240_VTU_OP_LOAD |
				(as->vlan_id[j] << AR7240_VTU_VID_S),
				as->vlan_table[j]);
		}
	} else {
		/* vlan disabled:
		 * isolate all ports, but connect them to the cpu port */
		for (i = 0; i < as->swdev.ports; i++) {
			if (i == AR7240_PORT_CPU)
				continue;

			portmask[i] = 1 << AR7240_PORT_CPU;
			portmask[AR7240_PORT_CPU] |= (1 << i);
		}
	}

	/* update the port destination mask registers and tag settings */
	for (i = 0; i < as->swdev.ports; i++)
		ar7240sw_setup_port(as, i, portmask[i]);

	return 0;
}