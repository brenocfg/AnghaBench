#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct al_pcie_regs {TYPE_1__* port_regs; } ;
struct TYPE_4__ {int nof_p_hdr; int nof_np_hdr; } ;
struct al_pcie_port {TYPE_2__ ib_hcrd_config; struct al_pcie_regs* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  vc0_non_posted_rcv_q_ctrl; int /*<<< orphan*/  vc0_posted_rcv_q_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADM_NPQ_HCRD_VC0_MASK ; 
 int RADM_NPQ_HCRD_VC0_SHIFT ; 
 int /*<<< orphan*/  RADM_PQ_HCRD_VC0_MASK ; 
 int RADM_PQ_HCRD_VC0_SHIFT ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
al_pcie_port_ib_hcrd_config(struct al_pcie_port *pcie_port)
{
	struct al_pcie_regs *regs = pcie_port->regs;

	al_reg_write32_masked(
		&regs->port_regs->vc0_posted_rcv_q_ctrl,
		RADM_PQ_HCRD_VC0_MASK,
		(pcie_port->ib_hcrd_config.nof_p_hdr - 1)
			<< RADM_PQ_HCRD_VC0_SHIFT);

	al_reg_write32_masked(
		&regs->port_regs->vc0_non_posted_rcv_q_ctrl,
		RADM_NPQ_HCRD_VC0_MASK,
		(pcie_port->ib_hcrd_config.nof_np_hdr - 1)
			<< RADM_NPQ_HCRD_VC0_SHIFT);
}