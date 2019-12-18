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
struct pcicfg_pcie {int pcie_location; int pcie_flags; scalar_t__ pcie_type; int /*<<< orphan*/  pcie_slot_ctl2; int /*<<< orphan*/  pcie_link_ctl2; int /*<<< orphan*/  pcie_device_ctl2; int /*<<< orphan*/  pcie_root_ctl; int /*<<< orphan*/  pcie_slot_ctl; int /*<<< orphan*/  pcie_link_ctl; int /*<<< orphan*/  pcie_device_ctl; } ;
struct TYPE_2__ {struct pcicfg_pcie pcie; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_FLAGS_SLOT ; 
 int PCIEM_FLAGS_VERSION ; 
 scalar_t__ PCIEM_TYPE_DOWNSTREAM_PORT ; 
 scalar_t__ PCIEM_TYPE_ENDPOINT ; 
 scalar_t__ PCIEM_TYPE_LEGACY_ENDPOINT ; 
 scalar_t__ PCIEM_TYPE_ROOT_EC ; 
 scalar_t__ PCIEM_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  PCIER_DEVICE_CTL ; 
 int /*<<< orphan*/  PCIER_DEVICE_CTL2 ; 
 int /*<<< orphan*/  PCIER_LINK_CTL ; 
 int /*<<< orphan*/  PCIER_LINK_CTL2 ; 
 int /*<<< orphan*/  PCIER_ROOT_CTL ; 
 int /*<<< orphan*/  PCIER_SLOT_CTL ; 
 int /*<<< orphan*/  PCIER_SLOT_CTL2 ; 
 int /*<<< orphan*/  WREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_cfg_restore_pcie(device_t dev, struct pci_devinfo *dinfo)
{
#define	WREG(n, v)	pci_write_config(dev, pos + (n), (v), 2)
	struct pcicfg_pcie *cfg;
	int version, pos;

	cfg = &dinfo->cfg.pcie;
	pos = cfg->pcie_location;

	version = cfg->pcie_flags & PCIEM_FLAGS_VERSION;

	WREG(PCIER_DEVICE_CTL, cfg->pcie_device_ctl);

	if (version > 1 || cfg->pcie_type == PCIEM_TYPE_ROOT_PORT ||
	    cfg->pcie_type == PCIEM_TYPE_ENDPOINT ||
	    cfg->pcie_type == PCIEM_TYPE_LEGACY_ENDPOINT)
		WREG(PCIER_LINK_CTL, cfg->pcie_link_ctl);

	if (version > 1 || (cfg->pcie_type == PCIEM_TYPE_ROOT_PORT ||
	    (cfg->pcie_type == PCIEM_TYPE_DOWNSTREAM_PORT &&
	     (cfg->pcie_flags & PCIEM_FLAGS_SLOT))))
		WREG(PCIER_SLOT_CTL, cfg->pcie_slot_ctl);

	if (version > 1 || cfg->pcie_type == PCIEM_TYPE_ROOT_PORT ||
	    cfg->pcie_type == PCIEM_TYPE_ROOT_EC)
		WREG(PCIER_ROOT_CTL, cfg->pcie_root_ctl);

	if (version > 1) {
		WREG(PCIER_DEVICE_CTL2, cfg->pcie_device_ctl2);
		WREG(PCIER_LINK_CTL2, cfg->pcie_link_ctl2);
		WREG(PCIER_SLOT_CTL2, cfg->pcie_slot_ctl2);
	}
#undef WREG
}