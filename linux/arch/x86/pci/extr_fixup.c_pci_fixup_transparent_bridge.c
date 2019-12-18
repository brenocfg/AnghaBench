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
struct pci_dev {int device; int transparent; } ;

/* Variables and functions */

__attribute__((used)) static void pci_fixup_transparent_bridge(struct pci_dev *dev)
{
	if ((dev->device & 0xff00) == 0x2400)
		dev->transparent = 1;
}