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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCIC_BASEPERIPH ; 
#define  PCIP_BASEPERIPH_PIC_IOX_APIC 129 
#define  PCIP_BASEPERIPH_PIC_IO_APIC 128 
 scalar_t__ PCIS_BASEPERIPH_PIC ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ioapic_pci_probe(device_t dev)
{

	if (pci_get_class(dev) == PCIC_BASEPERIPH &&
	    pci_get_subclass(dev) == PCIS_BASEPERIPH_PIC) {
		switch (pci_get_progif(dev)) {
		case PCIP_BASEPERIPH_PIC_IO_APIC:
			device_set_desc(dev, "IO APIC");
			break;
		case PCIP_BASEPERIPH_PIC_IOX_APIC:
			device_set_desc(dev, "IO(x) APIC");
			break;
		default:
			return (ENXIO);
		}
		device_quiet(dev);
		return (-10000);
	}
	return (ENXIO);
}