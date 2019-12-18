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
 int /*<<< orphan*/  BUS_RESUME_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
#define  PCIC_BASEPERIPH 131 
#define  PCIC_BRIDGE 130 
#define  PCIC_DISPLAY 129 
#define  PCIC_MEMORY 128 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pci_get_class (int /*<<< orphan*/ ) ; 

int
pci_resume(device_t dev)
{
	device_t child, *devlist;
	int error, i, numdevs;

	if ((error = device_get_children(dev, &devlist, &numdevs)) != 0)
		return (error);

	/*
	 * Resume critical devices first, then everything else later.
	 */
	for (i = 0; i < numdevs; i++) {
		child = devlist[i];
		switch (pci_get_class(child)) {
		case PCIC_DISPLAY:
		case PCIC_MEMORY:
		case PCIC_BRIDGE:
		case PCIC_BASEPERIPH:
			BUS_RESUME_CHILD(dev, child);
			break;
		}
	}
	for (i = 0; i < numdevs; i++) {
		child = devlist[i];
		switch (pci_get_class(child)) {
		case PCIC_DISPLAY:
		case PCIC_MEMORY:
		case PCIC_BRIDGE:
		case PCIC_BASEPERIPH:
			break;
		default:
			BUS_RESUME_CHILD(dev, child);
		}
	}
	free(devlist, M_TEMP);
	return (0);
}