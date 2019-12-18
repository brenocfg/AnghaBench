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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  conf; } ;
struct TYPE_4__ {int /*<<< orphan*/  pf_sel; } ;
struct TYPE_6__ {TYPE_2__ pcie_global; TYPE_1__ axi_attr_ovrd; } ;
struct al_pcie_regs {TYPE_3__ axi; } ;
struct al_pcie_port {scalar_t__ rev_id; int /*<<< orphan*/  port_id; struct al_pcie_regs* regs; } ;
typedef  enum al_pcie_operating_mode { ____Placeholder_al_pcie_operating_mode } al_pcie_operating_mode ;

/* Variables and functions */
 int AL_PCIE_OPERATING_MODE_EP ; 
 int AL_PCIE_OPERATING_MODE_RC ; 
 scalar_t__ AL_PCIE_REV_ID_3 ; 
 scalar_t__ AL_REG_FIELD_GET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AL_REG_FIELD_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_CFG_PF_BIT0_OVRD ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_CFG_PF_BIT1_OVRD ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_ADDR_OFFSET_MASK ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_OVRD_FROM_AXUSER ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_OVRD_FROM_REG ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_ADDR_OFFSET_MASK ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_OVRD_FROM_AXUSER ; 
 int PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_OVRD_FROM_REG ; 
 scalar_t__ PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_EP ; 
 int /*<<< orphan*/  PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_MASK ; 
 scalar_t__ PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_RC ; 
 int /*<<< orphan*/  PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_SHIFT ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ al_pcie_port_is_enabled (struct al_pcie_port*) ; 
 scalar_t__ al_reg_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ ,int,int) ; 

int
al_pcie_port_operating_mode_config(
	struct al_pcie_port *pcie_port,
	enum al_pcie_operating_mode mode)
{
	struct al_pcie_regs *regs = pcie_port->regs;
	uint32_t reg, device_type, new_device_type;

	if (al_pcie_port_is_enabled(pcie_port)) {
		al_err("PCIe %d: already enabled, cannot set operating mode\n",
			pcie_port->port_id);
		return -EINVAL;
	}

	reg = al_reg_read32(regs->axi.pcie_global.conf);

	device_type = AL_REG_FIELD_GET(reg,
			PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_MASK,
			PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_SHIFT);
	if (mode == AL_PCIE_OPERATING_MODE_EP) {
		new_device_type = PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_EP;
	} else if (mode == AL_PCIE_OPERATING_MODE_RC) {
		new_device_type = PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_RC;

		if (pcie_port->rev_id == AL_PCIE_REV_ID_3) {
			/* config 1 PF in RC mode */
			al_reg_write32_masked(regs->axi.axi_attr_ovrd.pf_sel,
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_OVRD_FROM_AXUSER |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_OVRD_FROM_REG |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_ADDR_OFFSET_MASK |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_CFG_PF_BIT0_OVRD |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_OVRD_FROM_AXUSER |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_OVRD_FROM_REG |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_ADDR_OFFSET_MASK |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_CFG_PF_BIT1_OVRD,
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT0_OVRD_FROM_REG |
				PCIE_AXI_AXI_ATTR_OVRD_PF_SEL_PF_BIT1_OVRD_FROM_REG);
		}
	} else {
		al_err("PCIe %d: unknown operating mode: %d\n", pcie_port->port_id, mode);
		return -EINVAL;
	}

	if (new_device_type == device_type) {
		al_dbg("PCIe %d: operating mode already set to %s\n",
		       pcie_port->port_id, (mode == AL_PCIE_OPERATING_MODE_EP) ?
		       "EndPoint" : "Root Complex");
		return 0;
	}
	al_dbg("PCIe %d: set operating mode to %s\n",
		pcie_port->port_id, (mode == AL_PCIE_OPERATING_MODE_EP) ?
		"EndPoint" : "Root Complex");
	AL_REG_FIELD_SET(reg, PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_MASK,
			 PCIE_AXI_MISC_PCIE_GLOBAL_CONF_DEV_TYPE_SHIFT,
			 new_device_type);

	al_reg_write32(regs->axi.pcie_global.conf, reg);

	return 0;
}