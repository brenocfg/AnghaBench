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
struct resource {int dummy; } ;
struct ata_pci_controller {TYPE_1__* interrupt; scalar_t__ legacy; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {void* argument; int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int ATA_PCI_MAX_CH ; 
 int BUS_SETUP_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 int EINVAL ; 
 scalar_t__ ata_devclass ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ata_pci_setup_intr(device_t dev, device_t child, struct resource *irq, 
		   int flags, driver_filter_t *filter, driver_intr_t *function, 
		   void *argument, void **cookiep)
{
	struct ata_pci_controller *controller = device_get_softc(dev);

	if (controller->legacy) {
		return BUS_SETUP_INTR(device_get_parent(dev), child, irq,
			      flags, filter, function, argument, cookiep);
	} else {
		struct ata_pci_controller *controller = device_get_softc(dev);
		int unit;

	    	if (filter != NULL) {
			printf("ata-pci.c: we cannot use a filter here\n");
			return (EINVAL);
		}
		if (device_get_devclass(child) == ata_devclass)
			unit = ((struct ata_channel *)device_get_softc(child))->unit;
		else
			unit = ATA_PCI_MAX_CH - 1;
		controller->interrupt[unit].function = function;
		controller->interrupt[unit].argument = argument;
		*cookiep = controller;
		return 0;
	}
}