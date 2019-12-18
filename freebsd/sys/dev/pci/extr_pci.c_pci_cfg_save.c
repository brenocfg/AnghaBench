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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ pcix_location; } ;
struct TYPE_6__ {scalar_t__ pcie_location; } ;
struct TYPE_5__ {void* br_control; void* br_pribus; void* br_secbus; void* br_subbus; void* br_seclat; } ;
struct TYPE_8__ {int hdrtype; int /*<<< orphan*/ * iov; TYPE_3__ pcix; TYPE_2__ pcie; void* subdevice; void* subvendor; TYPE_1__ bridge; void* maxlat; void* mingnt; void* revid; void* progif; void* subclass; void* baseclass; void* lattimer; void* cachelnsz; void* intpin; void* intline; void* cmdreg; void* device; void* vendor; } ;
struct pci_devinfo {TYPE_4__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIC_BASEPERIPH ; 
 int /*<<< orphan*/  PCIC_DISPLAY ; 
 int /*<<< orphan*/  PCIC_MEMORY ; 
 int /*<<< orphan*/  PCIC_STORAGE ; 
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_2 ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int /*<<< orphan*/  PCIR_INTPIN ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  PCIR_MAXLAT ; 
 int /*<<< orphan*/  PCIR_MINGNT ; 
 int /*<<< orphan*/  PCIR_PRIBUS_1 ; 
 int /*<<< orphan*/  PCIR_PRIBUS_2 ; 
 int /*<<< orphan*/  PCIR_PROGIF ; 
 int /*<<< orphan*/  PCIR_REVID ; 
 int /*<<< orphan*/  PCIR_SECBUS_1 ; 
 int /*<<< orphan*/  PCIR_SECBUS_2 ; 
 int /*<<< orphan*/  PCIR_SECLAT_1 ; 
 int /*<<< orphan*/  PCIR_SECLAT_2 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_1 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_2 ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBDEV_2 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_2 ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int PCI_POWERSTATE_D0 ; 
 int PCI_POWERSTATE_D3 ; 
 int /*<<< orphan*/  pci_cfg_save_pcie (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_cfg_save_pcix (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int pci_do_power_nodriver ; 
 int /*<<< orphan*/  pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_cfg_save (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,int) ; 

void
pci_cfg_save(device_t dev, struct pci_devinfo *dinfo, int setstate)
{
	uint32_t cls;
	int ps;

	/*
	 * Some drivers apparently write to these registers w/o updating our
	 * cached copy.  No harm happens if we update the copy, so do so here
	 * so we can restore them.  The COMMAND register is modified by the
	 * bus w/o updating the cache.  This should represent the normally
	 * writable portion of the 'defined' part of type 0/1/2 headers.
	 */
	dinfo->cfg.vendor = pci_read_config(dev, PCIR_VENDOR, 2);
	dinfo->cfg.device = pci_read_config(dev, PCIR_DEVICE, 2);
	dinfo->cfg.cmdreg = pci_read_config(dev, PCIR_COMMAND, 2);
	dinfo->cfg.intline = pci_read_config(dev, PCIR_INTLINE, 1);
	dinfo->cfg.intpin = pci_read_config(dev, PCIR_INTPIN, 1);
	dinfo->cfg.cachelnsz = pci_read_config(dev, PCIR_CACHELNSZ, 1);
	dinfo->cfg.lattimer = pci_read_config(dev, PCIR_LATTIMER, 1);
	dinfo->cfg.baseclass = pci_read_config(dev, PCIR_CLASS, 1);
	dinfo->cfg.subclass = pci_read_config(dev, PCIR_SUBCLASS, 1);
	dinfo->cfg.progif = pci_read_config(dev, PCIR_PROGIF, 1);
	dinfo->cfg.revid = pci_read_config(dev, PCIR_REVID, 1);
	switch (dinfo->cfg.hdrtype & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
		dinfo->cfg.subvendor = pci_read_config(dev, PCIR_SUBVEND_0, 2);
		dinfo->cfg.subdevice = pci_read_config(dev, PCIR_SUBDEV_0, 2);
		dinfo->cfg.mingnt = pci_read_config(dev, PCIR_MINGNT, 1);
		dinfo->cfg.maxlat = pci_read_config(dev, PCIR_MAXLAT, 1);
		break;
	case PCIM_HDRTYPE_BRIDGE:
		dinfo->cfg.bridge.br_seclat = pci_read_config(dev,
		    PCIR_SECLAT_1, 1);
		dinfo->cfg.bridge.br_subbus = pci_read_config(dev,
		    PCIR_SUBBUS_1, 1);
		dinfo->cfg.bridge.br_secbus = pci_read_config(dev,
		    PCIR_SECBUS_1, 1);
		dinfo->cfg.bridge.br_pribus = pci_read_config(dev,
		    PCIR_PRIBUS_1, 1);
		dinfo->cfg.bridge.br_control = pci_read_config(dev,
		    PCIR_BRIDGECTL_1, 2);
		break;
	case PCIM_HDRTYPE_CARDBUS:
		dinfo->cfg.bridge.br_seclat = pci_read_config(dev,
		    PCIR_SECLAT_2, 1);
		dinfo->cfg.bridge.br_subbus = pci_read_config(dev,
		    PCIR_SUBBUS_2, 1);
		dinfo->cfg.bridge.br_secbus = pci_read_config(dev,
		    PCIR_SECBUS_2, 1);
		dinfo->cfg.bridge.br_pribus = pci_read_config(dev,
		    PCIR_PRIBUS_2, 1);
		dinfo->cfg.bridge.br_control = pci_read_config(dev,
		    PCIR_BRIDGECTL_2, 2);
		dinfo->cfg.subvendor = pci_read_config(dev, PCIR_SUBVEND_2, 2);
		dinfo->cfg.subdevice = pci_read_config(dev, PCIR_SUBDEV_2, 2);
		break;
	}

	if (dinfo->cfg.pcie.pcie_location != 0)
		pci_cfg_save_pcie(dev, dinfo);

	if (dinfo->cfg.pcix.pcix_location != 0)
		pci_cfg_save_pcix(dev, dinfo);

#ifdef PCI_IOV
	if (dinfo->cfg.iov != NULL)
		pci_iov_cfg_save(dev, dinfo);
#endif

	/*
	 * don't set the state for display devices, base peripherals and
	 * memory devices since bad things happen when they are powered down.
	 * We should (a) have drivers that can easily detach and (b) use
	 * generic drivers for these devices so that some device actually
	 * attaches.  We need to make sure that when we implement (a) we don't
	 * power the device down on a reattach.
	 */
	cls = pci_get_class(dev);
	if (!setstate)
		return;
	switch (pci_do_power_nodriver)
	{
		case 0:		/* NO powerdown at all */
			return;
		case 1:		/* Conservative about what to power down */
			if (cls == PCIC_STORAGE)
				return;
			/*FALLTHROUGH*/
		case 2:		/* Aggressive about what to power down */
			if (cls == PCIC_DISPLAY || cls == PCIC_MEMORY ||
			    cls == PCIC_BASEPERIPH)
				return;
			/*FALLTHROUGH*/
		case 3:		/* Power down everything */
			break;
	}
	/*
	 * PCI spec says we can only go into D3 state from D0 state.
	 * Transition from D[12] into D0 before going to D3 state.
	 */
	ps = pci_get_powerstate(dev);
	if (ps != PCI_POWERSTATE_D0 && ps != PCI_POWERSTATE_D3)
		pci_set_powerstate(dev, PCI_POWERSTATE_D0);
	if (pci_get_powerstate(dev) != PCI_POWERSTATE_D3)
		pci_set_powerstate(dev, PCI_POWERSTATE_D3);
}