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
typedef  int u32 ;
struct pci_dn {int dummy; } ;

/* Variables and functions */
 int PCI_CAPABILITY_LIST ; 
 int PCI_CAP_LIST_ID ; 
 scalar_t__ PCI_CAP_LIST_NEXT ; 
 int PCI_STATUS ; 
 int PCI_STATUS_CAP_LIST ; 
 int /*<<< orphan*/  pnv_pci_cfg_read (struct pci_dn*,int,int,int*) ; 

__attribute__((used)) static int pnv_eeh_find_cap(struct pci_dn *pdn, int cap)
{
	int pos = PCI_CAPABILITY_LIST;
	int cnt = 48;   /* Maximal number of capabilities */
	u32 status, id;

	if (!pdn)
		return 0;

	/* Check if the device supports capabilities */
	pnv_pci_cfg_read(pdn, PCI_STATUS, 2, &status);
	if (!(status & PCI_STATUS_CAP_LIST))
		return 0;

	while (cnt--) {
		pnv_pci_cfg_read(pdn, pos, 1, &pos);
		if (pos < 0x40)
			break;

		pos &= ~3;
		pnv_pci_cfg_read(pdn, pos + PCI_CAP_LIST_ID, 1, &id);
		if (id == 0xff)
			break;

		/* Found */
		if (id == cap)
			return pos;

		/* Next one */
		pos += PCI_CAP_LIST_NEXT;
	}

	return 0;
}