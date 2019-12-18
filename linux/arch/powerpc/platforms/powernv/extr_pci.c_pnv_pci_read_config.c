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
typedef  int u32 ;
struct pnv_phb {int flags; } ;
struct pci_dn {scalar_t__ edev; TYPE_1__* phb; } ;
struct pci_bus {int dummy; } ;
struct TYPE_2__ {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int EEH_IO_ERROR_VALUE (int) ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PNV_PHB_FLAG_EEH ; 
 scalar_t__ eeh_dev_check_failure (scalar_t__) ; 
 struct pci_dn* pci_get_pdn_by_devfn (struct pci_bus*,unsigned int) ; 
 int /*<<< orphan*/  pnv_pci_cfg_check (struct pci_dn*) ; 
 int pnv_pci_cfg_read (struct pci_dn*,int,int,int*) ; 
 int /*<<< orphan*/  pnv_pci_config_check_eeh (struct pci_dn*) ; 

__attribute__((used)) static int pnv_pci_read_config(struct pci_bus *bus,
			       unsigned int devfn,
			       int where, int size, u32 *val)
{
	struct pci_dn *pdn;
	struct pnv_phb *phb;
	int ret;

	*val = 0xFFFFFFFF;
	pdn = pci_get_pdn_by_devfn(bus, devfn);
	if (!pdn)
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (!pnv_pci_cfg_check(pdn))
		return PCIBIOS_DEVICE_NOT_FOUND;

	ret = pnv_pci_cfg_read(pdn, where, size, val);
	phb = pdn->phb->private_data;
	if (phb->flags & PNV_PHB_FLAG_EEH && pdn->edev) {
		if (*val == EEH_IO_ERROR_VALUE(size) &&
		    eeh_dev_check_failure(pdn->edev))
                        return PCIBIOS_DEVICE_NOT_FOUND;
	} else {
		pnv_pci_config_check_eeh(pdn);
	}

	return ret;
}