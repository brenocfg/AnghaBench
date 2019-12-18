#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int es_vid; size_t es_vlangroup; int es_untagged_ports; int es_member_ports; scalar_t__ es_fid; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;
struct TYPE_11__ {int* vlans; int num_ports; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ e6000sw_softc_t ;

/* Variables and functions */
 scalar_t__ E6000SW_WAITREADY (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ETHERSWITCH_VID_VALID ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int VTU_BUSY ; 
 int /*<<< orphan*/  VTU_DATA ; 
 int /*<<< orphan*/  VTU_DATA2 ; 
 int VTU_GET_NEXT ; 
 int /*<<< orphan*/  VTU_OPERATION ; 
 int VTU_OP_MASK ; 
 int VTU_PORT (TYPE_2__*,int) ; 
 int VTU_PORT_MASK ; 
 int VTU_PORT_TAGGED ; 
 int VTU_PORT_UNTAGGED ; 
 int VTU_PPREG (TYPE_2__*) ; 
 int /*<<< orphan*/  VTU_VID ; 
 int VTU_VID_MASK ; 
 int VTU_VID_VALID ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int e6000sw_readreg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_writereg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
e6000sw_get_dot1q_vlan(e6000sw_softc_t *sc, etherswitch_vlangroup_t *vg)
{
	int i, port;
	uint32_t reg;

	vg->es_fid = 0;
	vg->es_vid = sc->vlans[vg->es_vlangroup];
	vg->es_untagged_ports = vg->es_member_ports = 0;
	if (vg->es_vid == 0)
		return (0);

	if (E6000SW_WAITREADY(sc, VTU_OPERATION, VTU_BUSY)) {
		device_printf(sc->dev, "VTU unit is busy, cannot access\n");
		return (EBUSY);
	}

	e6000sw_writereg(sc, REG_GLOBAL, VTU_VID, vg->es_vid - 1);

	reg = e6000sw_readreg(sc, REG_GLOBAL, VTU_OPERATION);
	reg &= ~VTU_OP_MASK;
	reg |= VTU_GET_NEXT | VTU_BUSY;
	e6000sw_writereg(sc, REG_GLOBAL, VTU_OPERATION, reg);
	if (E6000SW_WAITREADY(sc, VTU_OPERATION, VTU_BUSY)) {
		device_printf(sc->dev, "Timeout while reading\n");
		return (EBUSY);
	}

	reg = e6000sw_readreg(sc, REG_GLOBAL, VTU_VID);
	if (reg == VTU_VID_MASK || (reg & VTU_VID_VALID) == 0)
		return (EINVAL);
	if ((reg & VTU_VID_MASK) != vg->es_vid)
		return (EINVAL);

	vg->es_vid |= ETHERSWITCH_VID_VALID;
	reg = e6000sw_readreg(sc, REG_GLOBAL, VTU_DATA);
	for (i = 0; i < sc->num_ports; i++) {
		if (i == VTU_PPREG(sc))
			reg = e6000sw_readreg(sc, REG_GLOBAL, VTU_DATA2);
		port = (reg >> VTU_PORT(sc, i)) & VTU_PORT_MASK;
		if (port == VTU_PORT_UNTAGGED) {
			vg->es_untagged_ports |= (1 << i);
			vg->es_member_ports |= (1 << i);
		} else if (port == VTU_PORT_TAGGED)
			vg->es_member_ports |= (1 << i);
	}

	return (0);
}