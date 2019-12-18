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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int PCIC_DISPLAY ; 
 int PCIS_DISPLAY_VGA ; 
 int PCI_S3_VENDOR_ID ; 
 int /*<<< orphan*/  S3_CONFIG_IO ; 
 int /*<<< orphan*/  S3_CONFIG_IO_SIZE ; 
 int /*<<< orphan*/  S3_ENHANCED_IO ; 
 int /*<<< orphan*/  S3_ENHANCED_IO_SIZE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
s3pci_probe(device_t dev)
{
	u_int32_t vendor, class, subclass, device_id;

	device_id = pci_get_devid(dev);
	vendor = device_id & 0xffff;
	class = pci_get_class(dev);
	subclass = pci_get_subclass(dev);

	if ((class != PCIC_DISPLAY) || (subclass != PCIS_DISPLAY_VGA) ||
		(vendor != PCI_S3_VENDOR_ID))
		return ENXIO;

	device_set_desc(dev, "S3 graphic card");

	bus_set_resource(dev, SYS_RES_IOPORT, 0,
				S3_CONFIG_IO, S3_CONFIG_IO_SIZE);
	bus_set_resource(dev, SYS_RES_IOPORT, 1,
				S3_ENHANCED_IO, S3_ENHANCED_IO_SIZE);

	return BUS_PROBE_DEFAULT;

}