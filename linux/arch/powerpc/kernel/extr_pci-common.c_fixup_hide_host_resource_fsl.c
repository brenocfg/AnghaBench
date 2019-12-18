#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int class; scalar_t__ hdr_type; TYPE_2__* resource; TYPE_1__* bus; } ;
struct TYPE_4__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int DEVICE_COUNT_RESOURCE ; 
 int PCI_CLASS_BRIDGE_OTHER ; 
 int PCI_CLASS_PROCESSOR_POWERPC ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 

__attribute__((used)) static void fixup_hide_host_resource_fsl(struct pci_dev *dev)
{
	int i, class = dev->class >> 8;
	/* When configured as agent, programing interface = 1 */
	int prog_if = dev->class & 0xf;

	if ((class == PCI_CLASS_PROCESSOR_POWERPC ||
	     class == PCI_CLASS_BRIDGE_OTHER) &&
		(dev->hdr_type == PCI_HEADER_TYPE_NORMAL) &&
		(prog_if == 0) &&
		(dev->bus->parent == NULL)) {
		for (i = 0; i < DEVICE_COUNT_RESOURCE; i++) {
			dev->resource[i].start = 0;
			dev->resource[i].end = 0;
			dev->resource[i].flags = 0;
		}
	}
}