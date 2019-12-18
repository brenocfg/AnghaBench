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
struct pci_dev {int mmio_always_on; } ;

/* Variables and functions */

__attribute__((used)) static void cs5536_isa_mmio_always_on(struct pci_dev *dev)
{
	dev->mmio_always_on = 1;
}