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
typedef  scalar_t__ u32 ;
struct pci_pbm_info {scalar_t__ portid; struct pci_pbm_info* next; } ;

/* Variables and functions */
 struct pci_pbm_info* pci_pbm_root ; 

__attribute__((used)) static struct pci_pbm_info *psycho_find_sibling(u32 upa_portid)
{
	struct pci_pbm_info *pbm;

	for (pbm = pci_pbm_root; pbm; pbm = pbm->next) {
		if (pbm->portid == upa_portid)
			return pbm;
	}
	return NULL;
}