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
struct pci_dev {scalar_t__ devfn; TYPE_1__* resource; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int DEVICE_COUNT_RESOURCE ; 
 scalar_t__ pci_is_root_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7786_pci_fixup(struct pci_dev *dev)
{
	/*
	 * Prevent enumeration of root complex resources.
	 */
	if (pci_is_root_bus(dev->bus) && dev->devfn == 0) {
		int i;

		for (i = 0; i < DEVICE_COUNT_RESOURCE; i++) {
			dev->resource[i].start	= 0;
			dev->resource[i].end	= 0;
			dev->resource[i].flags	= 0;
		}
	}
}