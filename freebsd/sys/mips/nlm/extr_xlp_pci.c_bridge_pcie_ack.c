#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_MSI_STATUS ; 
#define  PIC_PCIE_0_IRQ 131 
#define  PIC_PCIE_1_IRQ 130 
#define  PIC_PCIE_2_IRQ 129 
#define  PIC_PCIE_3_IRQ 128 
 int /*<<< orphan*/  XLP_IO_PCIE0_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLP_IO_PCIE1_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLP_IO_PCIE2_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLP_IO_PCIE3_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_nodeid () ; 
 int /*<<< orphan*/  nlm_pcicfg_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_pci_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bridge_pcie_ack(int irq, void *arg)
{
	uint32_t node,reg;
	uint64_t base;

	node = nlm_nodeid();
	reg = PCIE_MSI_STATUS;

	switch (irq) {
		case PIC_PCIE_0_IRQ:
			base = nlm_pcicfg_base(XLP_IO_PCIE0_OFFSET(node));
			break;
		case PIC_PCIE_1_IRQ:
			base = nlm_pcicfg_base(XLP_IO_PCIE1_OFFSET(node));
			break;
		case PIC_PCIE_2_IRQ:
			base = nlm_pcicfg_base(XLP_IO_PCIE2_OFFSET(node));
			break;
		case PIC_PCIE_3_IRQ:
			base = nlm_pcicfg_base(XLP_IO_PCIE3_OFFSET(node));
			break;
		default:
			return;
	}

	nlm_write_pci_reg(base, reg, 0xFFFFFFFF);
	return;
}