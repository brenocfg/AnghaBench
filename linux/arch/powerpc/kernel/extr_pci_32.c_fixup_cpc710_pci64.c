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
struct pci_dev {TYPE_1__* resource; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static void
fixup_cpc710_pci64(struct pci_dev* dev)
{
	/* Hide the PCI64 BARs from the kernel as their content doesn't
	 * fit well in the resource management
	 */
	dev->resource[0].start = dev->resource[0].end = 0;
	dev->resource[0].flags = 0;
	dev->resource[1].start = dev->resource[1].end = 0;
	dev->resource[1].flags = 0;
}