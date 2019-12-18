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
 int PCI_CAP_LIST_ID ; 
 scalar_t__ PCI_CAP_LIST_NEXT ; 
 int pseries_eeh_cap_start (struct pci_dn*) ; 
 int /*<<< orphan*/  rtas_read_config (struct pci_dn*,int,int,int*) ; 

__attribute__((used)) static int pseries_eeh_find_cap(struct pci_dn *pdn, int cap)
{
	int pos = pseries_eeh_cap_start(pdn);
	int cnt = 48;	/* Maximal number of capabilities */
	u32 id;

	if (!pos)
		return 0;

        while (cnt--) {
		rtas_read_config(pdn, pos, 1, &pos);
		if (pos < 0x40)
			break;
		pos &= ~3;
		rtas_read_config(pdn, pos + PCI_CAP_LIST_ID, 1, &id);
		if (id == 0xff)
			break;
		if (id == cap)
			return pos;
		pos += PCI_CAP_LIST_NEXT;
	}

	return 0;
}