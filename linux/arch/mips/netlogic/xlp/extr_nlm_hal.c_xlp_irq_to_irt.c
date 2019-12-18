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
typedef  int uint32_t ;

/* Variables and functions */
#define  PIC_2XX_XHCI_0_IRQ 147 
#define  PIC_2XX_XHCI_1_IRQ 146 
#define  PIC_2XX_XHCI_2_IRQ 145 
#define  PIC_EHCI_0_IRQ 144 
#define  PIC_EHCI_1_IRQ 143 
#define  PIC_GPIO_IRQ 142 
#define  PIC_I2C_0_IRQ 141 
#define  PIC_I2C_1_IRQ 140 
#define  PIC_I2C_2_IRQ 139 
#define  PIC_I2C_3_IRQ 138 
 int PIC_IRT_PCIE_LINK_INDEX (scalar_t__) ; 
#define  PIC_MMC_IRQ 137 
#define  PIC_NAND_IRQ 136 
#define  PIC_OHCI_0_IRQ 135 
#define  PIC_OHCI_1_IRQ 134 
#define  PIC_OHCI_2_IRQ 133 
#define  PIC_OHCI_3_IRQ 132 
 int PIC_PCIE_LINK_LEGACY_IRQ (int) ; 
 scalar_t__ PIC_PCIE_LINK_LEGACY_IRQ_BASE ; 
#define  PIC_SATA_IRQ 131 
#define  PIC_SPI_IRQ 130 
#define  PIC_UART_0_IRQ 129 
#define  PIC_UART_1_IRQ 128 
 int XLP2XX_IO_I2C_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP2XX_IO_USB_XHCI0_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP2XX_IO_USB_XHCI1_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP2XX_IO_USB_XHCI2_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_GPIO_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_I2C0_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_MMC_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_NAND_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_SATA_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_SPI_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_UART0_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_UART1_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_USB_EHCI0_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_USB_EHCI1_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_USB_OHCI0_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_USB_OHCI1_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_USB_OHCI2_OFFSET (int /*<<< orphan*/ ) ; 
 int XLP_IO_USB_OHCI3_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLP_PCI_IRTINFO_REG ; 
 int /*<<< orphan*/  cpu_is_xlpii () ; 
 int /*<<< orphan*/  nlm_pcicfg_base (int) ; 
 int nlm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlp_irq_to_irt(int irq)
{
	uint64_t pcibase;
	int devoff, irt;

	devoff = 0;
	switch (irq) {
	case PIC_UART_0_IRQ:
		devoff = XLP_IO_UART0_OFFSET(0);
		break;
	case PIC_UART_1_IRQ:
		devoff = XLP_IO_UART1_OFFSET(0);
		break;
	case PIC_MMC_IRQ:
		devoff = XLP_IO_MMC_OFFSET(0);
		break;
	case PIC_I2C_0_IRQ:	/* I2C will be fixed up */
	case PIC_I2C_1_IRQ:
	case PIC_I2C_2_IRQ:
	case PIC_I2C_3_IRQ:
		if (cpu_is_xlpii())
			devoff = XLP2XX_IO_I2C_OFFSET(0);
		else
			devoff = XLP_IO_I2C0_OFFSET(0);
		break;
	case PIC_SATA_IRQ:
		devoff = XLP_IO_SATA_OFFSET(0);
		break;
	case PIC_GPIO_IRQ:
		devoff = XLP_IO_GPIO_OFFSET(0);
		break;
	case PIC_NAND_IRQ:
		devoff = XLP_IO_NAND_OFFSET(0);
		break;
	case PIC_SPI_IRQ:
		devoff = XLP_IO_SPI_OFFSET(0);
		break;
	default:
		if (cpu_is_xlpii()) {
			switch (irq) {
				/* XLP2XX has three XHCI USB controller */
			case PIC_2XX_XHCI_0_IRQ:
				devoff = XLP2XX_IO_USB_XHCI0_OFFSET(0);
				break;
			case PIC_2XX_XHCI_1_IRQ:
				devoff = XLP2XX_IO_USB_XHCI1_OFFSET(0);
				break;
			case PIC_2XX_XHCI_2_IRQ:
				devoff = XLP2XX_IO_USB_XHCI2_OFFSET(0);
				break;
			}
		} else {
			switch (irq) {
			case PIC_EHCI_0_IRQ:
				devoff = XLP_IO_USB_EHCI0_OFFSET(0);
				break;
			case PIC_EHCI_1_IRQ:
				devoff = XLP_IO_USB_EHCI1_OFFSET(0);
				break;
			case PIC_OHCI_0_IRQ:
				devoff = XLP_IO_USB_OHCI0_OFFSET(0);
				break;
			case PIC_OHCI_1_IRQ:
				devoff = XLP_IO_USB_OHCI1_OFFSET(0);
				break;
			case PIC_OHCI_2_IRQ:
				devoff = XLP_IO_USB_OHCI2_OFFSET(0);
				break;
			case PIC_OHCI_3_IRQ:
				devoff = XLP_IO_USB_OHCI3_OFFSET(0);
				break;
			}
		}
	}

	if (devoff != 0) {
		uint32_t val;

		pcibase = nlm_pcicfg_base(devoff);
		val = nlm_read_reg(pcibase, XLP_PCI_IRTINFO_REG);
		if (val == 0xffffffff) {
			irt = -1;
		} else {
			irt = val & 0xffff;
			/* HW weirdness, I2C IRT entry has to be fixed up */
			switch (irq) {
			case PIC_I2C_1_IRQ:
				irt = irt + 1; break;
			case PIC_I2C_2_IRQ:
				irt = irt + 2; break;
			case PIC_I2C_3_IRQ:
				irt = irt + 3; break;
			}
		}
	} else if (irq >= PIC_PCIE_LINK_LEGACY_IRQ(0) &&
			irq <= PIC_PCIE_LINK_LEGACY_IRQ(3)) {
		/* HW bug, PCI IRT entries are bad on early silicon, fix */
		irt = PIC_IRT_PCIE_LINK_INDEX(irq -
					PIC_PCIE_LINK_LEGACY_IRQ_BASE);
	} else {
		irt = -1;
	}
	return irt;
}