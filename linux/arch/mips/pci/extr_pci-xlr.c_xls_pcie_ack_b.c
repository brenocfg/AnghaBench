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
struct irq_data {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLOGIC_IO_PCIE_1_OFFSET ; 
#define  PIC_PCIE_LINK0_IRQ 131 
#define  PIC_PCIE_LINK1_IRQ 130 
#define  PIC_PCIE_XLSB0_LINK2_IRQ 129 
#define  PIC_PCIE_XLSB0_LINK3_IRQ 128 
 int /*<<< orphan*/  nlm_mmio_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_reg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xls_pcie_ack_b(struct irq_data *d)
{
	uint64_t pciebase_le = nlm_mmio_base(NETLOGIC_IO_PCIE_1_OFFSET);

	switch (d->irq) {
	case PIC_PCIE_LINK0_IRQ:
		nlm_write_reg(pciebase_le, (0x90 >> 2), 0xffffffff);
		break;
	case PIC_PCIE_LINK1_IRQ:
		nlm_write_reg(pciebase_le, (0x94 >> 2), 0xffffffff);
		break;
	case PIC_PCIE_XLSB0_LINK2_IRQ:
		nlm_write_reg(pciebase_le, (0x190 >> 2), 0xffffffff);
		break;
	case PIC_PCIE_XLSB0_LINK3_IRQ:
		nlm_write_reg(pciebase_le, (0x194 >> 2), 0xffffffff);
		break;
	}
}