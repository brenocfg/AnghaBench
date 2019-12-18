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
struct pci_dev {scalar_t__ pm_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void tc35815_fixup(struct pci_dev *dev)
{
	/* This device may have PM registers but not they are not supported. */
	if (dev->pm_cap) {
		dev_info(&dev->dev, "PM disabled\n");
		dev->pm_cap = 0;
	}
}