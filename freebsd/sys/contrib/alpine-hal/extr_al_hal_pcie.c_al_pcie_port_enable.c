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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pos_cntl; } ;
struct TYPE_7__ {TYPE_2__ ordering; } ;
struct al_pcie_regs {TYPE_3__ axi; } ;
struct TYPE_5__ {scalar_t__ nof_np_hdr; scalar_t__ nof_p_hdr; } ;
struct al_pcie_port {unsigned int port_id; scalar_t__ rev_id; TYPE_1__ ib_hcrd_config; struct al_pcie_regs* regs; scalar_t__ pbs_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  pcie_conf_1; } ;
struct al_pbs_regs {TYPE_4__ unit; } ;

/* Variables and functions */
 scalar_t__ AL_PCIE_REV_ID_1 ; 
 scalar_t__ AL_PCIE_REV_ID_2 ; 
 unsigned int PBS_UNIT_PCIE_CONF_1_PCIE_EXIST_SHIFT ; 
 int PCIE_AXI_CORE_SETUP_ATS_CAP_DIS ; 
 int /*<<< orphan*/  al_pcie_ib_hcrd_os_ob_reads_config_default (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int,int) ; 

int
al_pcie_port_enable(struct al_pcie_port *pcie_port)
{
	struct al_pbs_regs *pbs_reg_base =
				(struct al_pbs_regs *)pcie_port->pbs_regs;
	struct al_pcie_regs *regs = pcie_port->regs;
	unsigned int port_id = pcie_port->port_id;

	/* pre-port-enable default functionality should be here */

	/**
	 * Set inbound header credit and outstanding outbound reads defaults
	 * if the port initiator doesn't set it.
	 * Must be called before port enable (PCIE_EXIST)
	 */
	if ((pcie_port->ib_hcrd_config.nof_np_hdr == 0) ||
			(pcie_port->ib_hcrd_config.nof_p_hdr == 0))
		al_pcie_ib_hcrd_os_ob_reads_config_default(pcie_port);

	/*
	 * Disable ATS capability
	 * - must be done before core reset deasserted
	 * - rev_id 0 - no effect, but no harm
	 */
	if ((pcie_port->rev_id == AL_PCIE_REV_ID_1) ||
		(pcie_port->rev_id == AL_PCIE_REV_ID_2)) {
		al_reg_write32_masked(
			regs->axi.ordering.pos_cntl,
			PCIE_AXI_CORE_SETUP_ATS_CAP_DIS,
			PCIE_AXI_CORE_SETUP_ATS_CAP_DIS);
	}

	/* Deassert core reset */
	al_reg_write32_masked(
		&pbs_reg_base->unit.pcie_conf_1,
		1 << (port_id + PBS_UNIT_PCIE_CONF_1_PCIE_EXIST_SHIFT),
		1 << (port_id + PBS_UNIT_PCIE_CONF_1_PCIE_EXIST_SHIFT));

	return 0;
}