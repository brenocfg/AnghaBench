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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int MSI_MIPS_ADDR_BASE ; 
 int /*<<< orphan*/  PCIE_BRIDGE_CMD ; 
 int /*<<< orphan*/  PCIE_BRIDGE_MSI_ADDRH ; 
 int /*<<< orphan*/  PCIE_BRIDGE_MSI_ADDRL ; 
 int /*<<< orphan*/  PCIE_BRIDGE_MSI_CAP ; 
 int /*<<< orphan*/  PCIE_INT_EN0 ; 
 int /*<<< orphan*/  PCIE_MSI_EN ; 
 int PCIE_MSI_INT_EN ; 
 int PCIE_MSI_VECTOR_INT_EN ; 
 int PCIM_CMD_INTxDIS ; 
 int PCIM_MSICTRL_MMC_32 ; 
 int PCIM_MSICTRL_MSI_ENABLE ; 
 int PIC_PCIE_IRQ (int) ; 
 int /*<<< orphan*/  XLP_IO_PCIE_OFFSET (int,int) ; 
 int /*<<< orphan*/  bridge_pcie_ack ; 
 int /*<<< orphan*/  cpu_establish_hardintr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,int,void**) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int nlm_nodeid () ; 
 int /*<<< orphan*/  nlm_pcicfg_base (int /*<<< orphan*/ ) ; 
 int nlm_read_pci_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_pci_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rman_activate_resource (struct resource*) ; 
 int rman_get_end (struct resource*) ; 
 int rman_get_start (struct resource*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xlp_set_bus_ack (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mips_platform_pcib_setup_intr(device_t dev, device_t child,
    struct resource *irq, int flags, driver_filter_t *filt,
    driver_intr_t *intr, void *arg, void **cookiep)
{
	int error = 0;
	int xlpirq;

	error = rman_activate_resource(irq);
	if (error)
		return error;
	if (rman_get_start(irq) != rman_get_end(irq)) {
		device_printf(dev, "Interrupt allocation %ju != %ju\n",
		    rman_get_start(irq), rman_get_end(irq));
		return (EINVAL);
	}
	xlpirq = rman_get_start(irq);
	if (xlpirq == 0)
		return (0);

	if (strcmp(device_get_name(dev), "pcib") != 0)
		return (0);

	/*
	 * temporary hack for MSI, we support just one device per
	 * link, and assign the link interrupt to the device interrupt
	 */
	if (xlpirq >= 64) {
		int node, val, link;
		uint64_t base;

		xlpirq -= 64;
		if (xlpirq % 32 != 0)
			return (0);

		node = nlm_nodeid();
		link = xlpirq / 32;
		base = nlm_pcicfg_base(XLP_IO_PCIE_OFFSET(node,link));

		/* MSI Interrupt Vector enable at bridge's configuration */
		nlm_write_pci_reg(base, PCIE_MSI_EN, PCIE_MSI_VECTOR_INT_EN);

		val = nlm_read_pci_reg(base, PCIE_INT_EN0);
		/* MSI Interrupt enable at bridge's configuration */
		nlm_write_pci_reg(base, PCIE_INT_EN0,
		    (val | PCIE_MSI_INT_EN));

		/* legacy interrupt disable at bridge */
		val = nlm_read_pci_reg(base, PCIE_BRIDGE_CMD);
		nlm_write_pci_reg(base, PCIE_BRIDGE_CMD,
		    (val | PCIM_CMD_INTxDIS));

		/* MSI address update at bridge */
		nlm_write_pci_reg(base, PCIE_BRIDGE_MSI_ADDRL,
		    MSI_MIPS_ADDR_BASE);
		nlm_write_pci_reg(base, PCIE_BRIDGE_MSI_ADDRH, 0);

		val = nlm_read_pci_reg(base, PCIE_BRIDGE_MSI_CAP);
		/* MSI capability enable at bridge */
		nlm_write_pci_reg(base, PCIE_BRIDGE_MSI_CAP,
		    (val | (PCIM_MSICTRL_MSI_ENABLE << 16) |
		        (PCIM_MSICTRL_MMC_32 << 16)));
		xlpirq = PIC_PCIE_IRQ(link);
	}

	/* if it is for real PCIe, we need to ack at bridge too */
	if (xlpirq >= PIC_PCIE_IRQ(0) && xlpirq <= PIC_PCIE_IRQ(3))
		xlp_set_bus_ack(xlpirq, bridge_pcie_ack, NULL);
	cpu_establish_hardintr(device_get_name(child), filt, intr, arg,
	    xlpirq, flags, cookiep);

	return (0);
}