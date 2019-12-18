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
struct pcicfg_iov {int iov_pos; } ;
struct TYPE_2__ {struct pcicfg_iov* iov; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_EA_BEI_BAR_0 ; 
 int PCIM_EA_BEI_BAR_5 ; 
 int PCIM_EA_BEI_ROM ; 
 int PCIM_EA_BEI_VF_BAR_0 ; 
 int PCIM_EA_BEI_VF_BAR_5 ; 
 int PCIR_BAR (int) ; 
 int PCIR_BIOS ; 
 int PCIR_SRIOV_BAR (int) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_ea_bei_to_rid(device_t dev, int bei)
{
#ifdef PCI_IOV
	struct pci_devinfo *dinfo;
	int iov_pos;
	struct pcicfg_iov *iov;

	dinfo = device_get_ivars(dev);
	iov = dinfo->cfg.iov;
	if (iov != NULL)
		iov_pos = iov->iov_pos;
	else
		iov_pos = 0;
#endif

	/* Check if matches BAR */
	if ((bei >= PCIM_EA_BEI_BAR_0) &&
	    (bei <= PCIM_EA_BEI_BAR_5))
		return (PCIR_BAR(bei));

	/* Check ROM */
	if (bei == PCIM_EA_BEI_ROM)
		return (PCIR_BIOS);

#ifdef PCI_IOV
	/* Check if matches VF_BAR */
	if ((iov != NULL) && (bei >= PCIM_EA_BEI_VF_BAR_0) &&
	    (bei <= PCIM_EA_BEI_VF_BAR_5))
		return (PCIR_SRIOV_BAR(bei - PCIM_EA_BEI_VF_BAR_0) +
		    iov_pos);
#endif

	return (-1);
}