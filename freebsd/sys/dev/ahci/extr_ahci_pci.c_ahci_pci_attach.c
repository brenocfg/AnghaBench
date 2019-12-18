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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ahci_controller {int quirks; int vendorid; int subvendorid; int subdeviceid; scalar_t__ r_rid; int remap_offset; int remap_size; scalar_t__ remapped_devices; scalar_t__ r_msix_tab_rid; scalar_t__ r_msix_pba_rid; int msi; int numirqs; int /*<<< orphan*/ * r_msix_pba; int /*<<< orphan*/ * r_msix_table; void* r_mem; int /*<<< orphan*/  deviceid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ id; scalar_t__ rev; int quirks; } ;

/* Variables and functions */
 int AHCI_Q_1MSI ; 
 int AHCI_Q_ABAR0 ; 
 int AHCI_Q_NOMSI ; 
 int AHCI_Q_NOMSIX ; 
 int AHCI_Q_SATA1_UNIT0 ; 
 int AHCI_VSCAP ; 
 int ATA_INL (void*,int) ; 
 int ENXIO ; 
 int PCIC_STORAGE ; 
 int PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0 ; 
 void* PCIR_BAR (int) ; 
 int PCIS_STORAGE_NVM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int ahci_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahci_free_mem (int /*<<< orphan*/ ) ; 
 TYPE_1__* ahci_ids ; 
 int ahci_pci_ctlr_reset (int /*<<< orphan*/ ) ; 
 int ahci_pci_read_msix_bars (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int min (int,int) ; 
 int pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_revid (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_msi_count (int /*<<< orphan*/ ) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
ahci_pci_attach(device_t dev)
{
	struct ahci_controller *ctlr = device_get_softc(dev);
	int	error, i;
	uint32_t devid = pci_get_devid(dev);
	uint8_t revid = pci_get_revid(dev);
	int msi_count, msix_count;
	uint8_t table_bar = 0, pba_bar = 0;

	msi_count = pci_msi_count(dev);
	msix_count = pci_msix_count(dev);

	i = 0;
	while (ahci_ids[i].id != 0 &&
	    (ahci_ids[i].id != devid ||
	     ahci_ids[i].rev > revid))
		i++;
	ctlr->quirks = ahci_ids[i].quirks;
	/* Limit speed for my onboard JMicron external port.
	 * It is not eSATA really, limit to SATA 1 */
	if (pci_get_devid(dev) == 0x2363197b &&
	    pci_get_subvendor(dev) == 0x1043 &&
	    pci_get_subdevice(dev) == 0x81e4)
		ctlr->quirks |= AHCI_Q_SATA1_UNIT0;
	resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "quirks", &ctlr->quirks);
	ctlr->vendorid = pci_get_vendor(dev);
	ctlr->deviceid = pci_get_device(dev);
	ctlr->subvendorid = pci_get_subvendor(dev);
	ctlr->subdeviceid = pci_get_subdevice(dev);

	/* Default AHCI Base Address is BAR(5), Cavium uses BAR(0) */
	if (ctlr->quirks & AHCI_Q_ABAR0)
		ctlr->r_rid = PCIR_BAR(0);
	else
		ctlr->r_rid = PCIR_BAR(5);
	if (!(ctlr->r_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &ctlr->r_rid, RF_ACTIVE)))
		return ENXIO;

	/*
	 * Intel RAID hardware can remap NVMe devices inside its BAR.
	 * Try to detect this. Either we have to add the device
	 * here, or the user has to change the mode in the BIOS
	 * from RST to AHCI.
	 */
	if (pci_get_vendor(dev) == 0x8086) {
		uint32_t vscap;

		vscap = ATA_INL(ctlr->r_mem, AHCI_VSCAP);
		if (vscap & 1) {
			uint32_t cap = ATA_INL(ctlr->r_mem, 0x800); /* Intel's REMAP CAP */
			int i;

			ctlr->remap_offset = 0x4000;
			ctlr->remap_size = 0x4000;

			/*
			 * Check each of the devices that might be remapped to
			 * make sure they are an nvme device. At the present,
			 * nvme are the only known devices remapped.
			 */
			for (i = 0; i < 3; i++) {
				if (cap & (1 << i) &&
				    (ATA_INL(ctlr->r_mem, 0x880 + i * 0x80) ==
				     ((PCIC_STORAGE << 16) |
				      (PCIS_STORAGE_NVM << 8) |
				      PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0))) {
					ctlr->remapped_devices++;
				}
			}

			/* If we have any remapped device, disable MSI */
			if (ctlr->remapped_devices > 0) {
				device_printf(dev, "Detected %d nvme remapped devices\n",
				    ctlr->remapped_devices);
				ctlr->quirks |= (AHCI_Q_NOMSIX | AHCI_Q_NOMSI);
			}
		}
	}


	if (ctlr->quirks & AHCI_Q_NOMSIX)
		msix_count = 0;

	/* Read MSI-x BAR IDs if supported */
	if (msix_count > 0) {
		error = ahci_pci_read_msix_bars(dev, &table_bar, &pba_bar);
		if (error == 0) {
			ctlr->r_msix_tab_rid = table_bar;
			ctlr->r_msix_pba_rid = pba_bar;
		} else {
			/* Failed to read BARs, disable MSI-x */
			msix_count = 0;
		}
	}

	/* Allocate resources for MSI-x table and PBA */
	if (msix_count > 0) {
		/*
		 * Allocate new MSI-x table only if not
		 * allocated before.
		 */
		ctlr->r_msix_table = NULL;
		if (ctlr->r_msix_tab_rid != ctlr->r_rid) {
			/* Separate BAR for MSI-x */
			ctlr->r_msix_table = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
			    &ctlr->r_msix_tab_rid, RF_ACTIVE);
			if (ctlr->r_msix_table == NULL) {
				ahci_free_mem(dev);
				return (ENXIO);
			}
		}

		/*
		 * Allocate new PBA table only if not
		 * allocated before.
		 */
		ctlr->r_msix_pba = NULL;
		if ((ctlr->r_msix_pba_rid != ctlr->r_msix_tab_rid) &&
		    (ctlr->r_msix_pba_rid != ctlr->r_rid)) {
			/* Separate BAR for PBA */
			ctlr->r_msix_pba = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
			    &ctlr->r_msix_pba_rid, RF_ACTIVE);
			if (ctlr->r_msix_pba == NULL) {
				ahci_free_mem(dev);
				return (ENXIO);
			}
		}
	}

	pci_enable_busmaster(dev);
	/* Reset controller */
	if ((error = ahci_pci_ctlr_reset(dev)) != 0) {
		ahci_free_mem(dev);
		return (error);
	}

	/* Setup interrupts. */

	/* Setup MSI register parameters */
	/* Process hints. */
	if (ctlr->quirks & AHCI_Q_NOMSI)
		ctlr->msi = 0;
	else if (ctlr->quirks & AHCI_Q_1MSI)
		ctlr->msi = 1;
	else
		ctlr->msi = 2;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "msi", &ctlr->msi);
	ctlr->numirqs = 1;
	if (msi_count == 0 && msix_count == 0)
		ctlr->msi = 0;
	if (ctlr->msi < 0)
		ctlr->msi = 0;
	else if (ctlr->msi == 1) {
		msi_count = min(1, msi_count);
		msix_count = min(1, msix_count);
	} else if (ctlr->msi > 1)
		ctlr->msi = 2;

	/* Allocate MSI/MSI-x if needed/present. */
	if (ctlr->msi > 0) {
		error = ENXIO;

		/* Try to allocate MSI-x first */
		if (msix_count > 0) {
			error = pci_alloc_msix(dev, &msix_count);
			if (error == 0)
				ctlr->numirqs = msix_count;
		}

		/*
		 * Try to allocate MSI if msi_count is greater than 0
		 * and if MSI-x allocation failed.
		 */
		if ((error != 0) && (msi_count > 0)) {
			error = pci_alloc_msi(dev, &msi_count);
			if (error == 0)
				ctlr->numirqs = msi_count;
		}

		/* Both MSI and MSI-x allocations failed */
		if (error != 0) {
			ctlr->msi = 0;
			device_printf(dev, "Failed to allocate MSI/MSI-x, "
			    "falling back to INTx\n");
		}
	}

	error = ahci_attach(dev);
	if (error != 0) {
		if (ctlr->msi > 0)
			pci_release_msi(dev);
		ahci_free_mem(dev);
	}
	return error;
}