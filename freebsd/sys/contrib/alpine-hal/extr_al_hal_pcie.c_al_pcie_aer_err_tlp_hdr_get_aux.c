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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_pcie_regs {TYPE_1__* core_space; } ;
struct al_pcie_port {struct al_pcie_regs* regs; } ;
struct al_pcie_core_aer_regs {int /*<<< orphan*/ * header_log; } ;
struct TYPE_2__ {struct al_pcie_core_aer_regs* aer; } ;

/* Variables and functions */
 int AL_PCIE_AER_ERR_TLP_HDR_NUM_DWORDS ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
al_pcie_aer_err_tlp_hdr_get_aux(
		struct al_pcie_port		*pcie_port,
		unsigned int	pf_num,
	uint32_t hdr[AL_PCIE_AER_ERR_TLP_HDR_NUM_DWORDS])
{
	struct al_pcie_regs *regs = pcie_port->regs;
	struct al_pcie_core_aer_regs *aer_regs = regs->core_space[pf_num].aer;
	int i;

	for (i = 0; i < AL_PCIE_AER_ERR_TLP_HDR_NUM_DWORDS; i++)
		hdr[i] = al_reg_read32(&aer_regs->header_log[i]);
}