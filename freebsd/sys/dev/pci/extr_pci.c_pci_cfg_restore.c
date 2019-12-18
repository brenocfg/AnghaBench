#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ msix_location; } ;
struct TYPE_10__ {scalar_t__ msi_location; } ;
struct TYPE_9__ {scalar_t__ pcix_location; } ;
struct TYPE_8__ {scalar_t__ pcie_location; } ;
struct TYPE_7__ {int /*<<< orphan*/  br_control; int /*<<< orphan*/  br_pribus; int /*<<< orphan*/  br_secbus; int /*<<< orphan*/  br_subbus; int /*<<< orphan*/  br_seclat; } ;
struct TYPE_12__ {int hdrtype; int /*<<< orphan*/ * iov; TYPE_5__ msix; TYPE_4__ msi; TYPE_3__ pcix; TYPE_2__ pcie; TYPE_1__ bridge; int /*<<< orphan*/  maxlat; int /*<<< orphan*/  mingnt; int /*<<< orphan*/  revid; int /*<<< orphan*/  progif; int /*<<< orphan*/  lattimer; int /*<<< orphan*/  cachelnsz; int /*<<< orphan*/  intpin; int /*<<< orphan*/  intline; int /*<<< orphan*/  cmdreg; } ;
struct pci_devinfo {TYPE_6__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_2 ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
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
 scalar_t__ PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  pci_cfg_restore_pcie (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_cfg_restore_pcix (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 scalar_t__ pci_get_powerstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_cfg_restore (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_restore_bars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resume_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resume_msix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
pci_cfg_restore(device_t dev, struct pci_devinfo *dinfo)
{

	/*
	 * Restore the device to full power mode.  We must do this
	 * before we restore the registers because moving from D3 to
	 * D0 will cause the chip's BARs and some other registers to
	 * be reset to some unknown power on reset values.  Cut down
	 * the noise on boot by doing nothing if we are already in
	 * state D0.
	 */
	if (pci_get_powerstate(dev) != PCI_POWERSTATE_D0)
		pci_set_powerstate(dev, PCI_POWERSTATE_D0);
	pci_write_config(dev, PCIR_COMMAND, dinfo->cfg.cmdreg, 2);
	pci_write_config(dev, PCIR_INTLINE, dinfo->cfg.intline, 1);
	pci_write_config(dev, PCIR_INTPIN, dinfo->cfg.intpin, 1);
	pci_write_config(dev, PCIR_CACHELNSZ, dinfo->cfg.cachelnsz, 1);
	pci_write_config(dev, PCIR_LATTIMER, dinfo->cfg.lattimer, 1);
	pci_write_config(dev, PCIR_PROGIF, dinfo->cfg.progif, 1);
	pci_write_config(dev, PCIR_REVID, dinfo->cfg.revid, 1);
	switch (dinfo->cfg.hdrtype & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
		pci_write_config(dev, PCIR_MINGNT, dinfo->cfg.mingnt, 1);
		pci_write_config(dev, PCIR_MAXLAT, dinfo->cfg.maxlat, 1);
		break;
	case PCIM_HDRTYPE_BRIDGE:
		pci_write_config(dev, PCIR_SECLAT_1,
		    dinfo->cfg.bridge.br_seclat, 1);
		pci_write_config(dev, PCIR_SUBBUS_1,
		    dinfo->cfg.bridge.br_subbus, 1);
		pci_write_config(dev, PCIR_SECBUS_1,
		    dinfo->cfg.bridge.br_secbus, 1);
		pci_write_config(dev, PCIR_PRIBUS_1,
		    dinfo->cfg.bridge.br_pribus, 1);
		pci_write_config(dev, PCIR_BRIDGECTL_1,
		    dinfo->cfg.bridge.br_control, 2);
		break;
	case PCIM_HDRTYPE_CARDBUS:
		pci_write_config(dev, PCIR_SECLAT_2,
		    dinfo->cfg.bridge.br_seclat, 1);
		pci_write_config(dev, PCIR_SUBBUS_2,
		    dinfo->cfg.bridge.br_subbus, 1);
		pci_write_config(dev, PCIR_SECBUS_2,
		    dinfo->cfg.bridge.br_secbus, 1);
		pci_write_config(dev, PCIR_PRIBUS_2,
		    dinfo->cfg.bridge.br_pribus, 1);
		pci_write_config(dev, PCIR_BRIDGECTL_2,
		    dinfo->cfg.bridge.br_control, 2);
		break;
	}
	pci_restore_bars(dev);

	/*
	 * Restore extended capabilities for PCI-Express and PCI-X
	 */
	if (dinfo->cfg.pcie.pcie_location != 0)
		pci_cfg_restore_pcie(dev, dinfo);
	if (dinfo->cfg.pcix.pcix_location != 0)
		pci_cfg_restore_pcix(dev, dinfo);

	/* Restore MSI and MSI-X configurations if they are present. */
	if (dinfo->cfg.msi.msi_location != 0)
		pci_resume_msi(dev);
	if (dinfo->cfg.msix.msix_location != 0)
		pci_resume_msix(dev);

#ifdef PCI_IOV
	if (dinfo->cfg.iov != NULL)
		pci_iov_cfg_restore(dev, dinfo);
#endif
}