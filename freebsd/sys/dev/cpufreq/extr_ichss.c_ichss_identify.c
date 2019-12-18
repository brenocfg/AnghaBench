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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pmbase ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 scalar_t__ ICHSS_BM_OFFSET ; 
 scalar_t__ ICHSS_CTRL_OFFSET ; 
 int ICHSS_IO_REG ; 
 int ICHSS_PMBASE_MASK ; 
 int /*<<< orphan*/  ICHSS_PMBASE_OFFSET ; 
 scalar_t__ PCI_DEV_82801BA ; 
 scalar_t__ PCI_DEV_82801CA ; 
 scalar_t__ PCI_DEV_82801DB ; 
 scalar_t__ PCI_DEV_82815_MC ; 
 scalar_t__ PCI_VENDOR_INTEL ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ich_device ; 
 int /*<<< orphan*/ * pci_find_bsf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ *) ; 
 int pci_get_revid (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ichss_identify(driver_t *driver, device_t parent)
{
	device_t child;
	uint32_t pmbase;

	if (resource_disabled("ichss", 0))
		return;

	/*
	 * It appears that ICH SpeedStep only requires a single CPU to
	 * set the value (since the chipset is shared by all CPUs.)
	 * Thus, we only add a child to cpu 0.
	 */
	if (device_get_unit(parent) != 0)
		return;

	/* Avoid duplicates. */
	if (device_find_child(parent, "ichss", -1))
		return;

	/*
	 * ICH2/3/4-M I/O Controller Hub is at bus 0, slot 1F, function 0.
	 * E.g. see Section 6.1 "PCI Devices and Functions" and table 6.1 of
	 * Intel(r) 82801BA I/O Controller Hub 2 (ICH2) and Intel(r) 82801BAM
	 * I/O Controller Hub 2 Mobile (ICH2-M).
	 */
	ich_device = pci_find_bsf(0, 0x1f, 0);
	if (ich_device == NULL ||
	    pci_get_vendor(ich_device) != PCI_VENDOR_INTEL ||
	    (pci_get_device(ich_device) != PCI_DEV_82801BA &&
	    pci_get_device(ich_device) != PCI_DEV_82801CA &&
	    pci_get_device(ich_device) != PCI_DEV_82801DB))
		return;

	/*
	 * Certain systems with ICH2 and an Intel 82815_MC host bridge
	 * where the host bridge's revision is < 5 lockup if SpeedStep
	 * is used.
	 */
	if (pci_get_device(ich_device) == PCI_DEV_82801BA) {
		device_t hostb;

		hostb = pci_find_bsf(0, 0, 0);
		if (hostb != NULL &&
		    pci_get_vendor(hostb) == PCI_VENDOR_INTEL &&
		    pci_get_device(hostb) == PCI_DEV_82815_MC &&
		    pci_get_revid(hostb) < 5)
			return;
	}

	/* Find the PMBASE register from our PCI config header. */
	pmbase = pci_read_config(ich_device, ICHSS_PMBASE_OFFSET,
	    sizeof(pmbase));
	if ((pmbase & ICHSS_IO_REG) == 0) {
		printf("ichss: invalid PMBASE memory type\n");
		return;
	}
	pmbase &= ICHSS_PMBASE_MASK;
	if (pmbase == 0) {
		printf("ichss: invalid zero PMBASE address\n");
		return;
	}
	DPRINT("ichss: PMBASE is %#x\n", pmbase);

	child = BUS_ADD_CHILD(parent, 20, "ichss", 0);
	if (child == NULL) {
		device_printf(parent, "add SpeedStep child failed\n");
		return;
	}

	/* Add the bus master arbitration and control registers. */
	bus_set_resource(child, SYS_RES_IOPORT, 0, pmbase + ICHSS_BM_OFFSET,
	    1);
	bus_set_resource(child, SYS_RES_IOPORT, 1, pmbase + ICHSS_CTRL_OFFSET,
	    1);
}