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
struct pcicfg_pcie {int pcie_location; int pcie_flags; scalar_t__ pcie_type; void* pcie_slot_ctl2; void* pcie_link_ctl2; void* pcie_device_ctl2; void* pcie_root_ctl; void* pcie_slot_ctl; void* pcie_link_ctl; void* pcie_device_ctl; } ;
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
 int /*<<< orphan*/  PCIER_FLAGS ; 
 int /*<<< orphan*/  PCIER_LINK_CTL ; 
 int /*<<< orphan*/  PCIER_LINK_CTL2 ; 
 int /*<<< orphan*/  PCIER_ROOT_CTL ; 
 int /*<<< orphan*/  PCIER_SLOT_CTL ; 
 int /*<<< orphan*/  PCIER_SLOT_CTL2 ; 
 void* RREG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_cfg_save_pcie(device_t dev, struct pci_devinfo *dinfo)
{
#define	RREG(n)	pci_read_config(dev, pos + (n), 2)
	struct pcicfg_pcie *cfg;
	int version, pos;

	cfg = &dinfo->cfg.pcie;
	pos = cfg->pcie_location;

	cfg->pcie_flags = RREG(PCIER_FLAGS);

	version = cfg->pcie_flags & PCIEM_FLAGS_VERSION;

	cfg->pcie_device_ctl = RREG(PCIER_DEVICE_CTL);

	if (version > 1 || cfg->pcie_type == PCIEM_TYPE_ROOT_PORT ||
	    cfg->pcie_type == PCIEM_TYPE_ENDPOINT ||
	    cfg->pcie_type == PCIEM_TYPE_LEGACY_ENDPOINT)
		cfg->pcie_link_ctl = RREG(PCIER_LINK_CTL);

	if (version > 1 || (cfg->pcie_type == PCIEM_TYPE_ROOT_PORT ||
	    (cfg->pcie_type == PCIEM_TYPE_DOWNSTREAM_PORT &&
	     (cfg->pcie_flags & PCIEM_FLAGS_SLOT))))
		cfg->pcie_slot_ctl = RREG(PCIER_SLOT_CTL);

	if (version > 1 || cfg->pcie_type == PCIEM_TYPE_ROOT_PORT ||
	    cfg->pcie_type == PCIEM_TYPE_ROOT_EC)
		cfg->pcie_root_ctl = RREG(PCIER_ROOT_CTL);

	if (version > 1) {
		cfg->pcie_device_ctl2 = RREG(PCIER_DEVICE_CTL2);
		cfg->pcie_link_ctl2 = RREG(PCIER_LINK_CTL2);
		cfg->pcie_slot_ctl2 = RREG(PCIER_SLOT_CTL2);
	}
#undef RREG
}