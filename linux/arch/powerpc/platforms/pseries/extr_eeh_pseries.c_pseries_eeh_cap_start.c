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
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_CAP_LIST ; 
 int /*<<< orphan*/  rtas_read_config (struct pci_dn*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int pseries_eeh_cap_start(struct pci_dn *pdn)
{
	u32 status;

	if (!pdn)
		return 0;

	rtas_read_config(pdn, PCI_STATUS, 2, &status);
	if (!(status & PCI_STATUS_CAP_LIST))
		return 0;

	return PCI_CAPABILITY_LIST;
}