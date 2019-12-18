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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bcmp (scalar_t__*,char*,int) ; 
 int le16toh (int) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__* x86bios_get_orm (int /*<<< orphan*/ ) ; 

int
x86bios_match_device(uint32_t offset, device_t dev)
{
	uint8_t *p;
	uint16_t device, vendor;
	uint8_t class, progif, subclass;

	/* Does the shadow ROM contain BIOS POST code for x86? */
	p = x86bios_get_orm(offset);
	if (p == NULL)
		return (0);

	/* Does it contain PCI data structure? */
	p += le16toh(*(uint16_t *)(p + 0x18));
	if (bcmp(p, "PCIR", 4) != 0 ||
	    le16toh(*(uint16_t *)(p + 0x0a)) < 0x18 || *(p + 0x14) != 0)
		return (0);

	/* Does it match the vendor, device, and classcode? */
	vendor = le16toh(*(uint16_t *)(p + 0x04));
	device = le16toh(*(uint16_t *)(p + 0x06));
	progif = *(p + 0x0d);
	subclass = *(p + 0x0e);
	class = *(p + 0x0f);
	if (vendor != pci_get_vendor(dev) || device != pci_get_device(dev) ||
	    class != pci_get_class(dev) || subclass != pci_get_subclass(dev) ||
	    progif != pci_get_progif(dev))
		return (0);

	return (1);
}