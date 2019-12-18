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
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCI_ID_MSI ; 
 int PCI_RID_DOMAIN_SHIFT ; 
 int pci_get_domain (int /*<<< orphan*/ ) ; 
 int pci_get_rid (int /*<<< orphan*/ ) ; 
 int pcib_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 

__attribute__((used)) static int
thunder_pem_get_id(device_t pci, device_t child, enum pci_id_type type,
    uintptr_t *id)
{
	int bsf;
	int pem;

	if (type != PCI_ID_MSI)
		return (pcib_get_id(pci, child, type, id));

	bsf = pci_get_rid(child);

	/* PEM (PCIe MAC/root complex) number is equal to domain */
	pem = pci_get_domain(child);

	/*
	 * Set appropriate device ID (passed by the HW along with
	 * the transaction to memory) for different root complex
	 * numbers using hard-coded domain portion for each group.
	 */
	if (pem < 3)
		*id = (0x1 << PCI_RID_DOMAIN_SHIFT) | bsf;
	else if (pem < 6)
		*id = (0x3 << PCI_RID_DOMAIN_SHIFT) | bsf;
	else if (pem < 9)
		*id = (0x9 << PCI_RID_DOMAIN_SHIFT) | bsf;
	else if (pem < 12)
		*id = (0xB << PCI_RID_DOMAIN_SHIFT) | bsf;
	else
		return (ENXIO);

	return (0);
}