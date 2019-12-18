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
struct sb1250_bus_dma_mask_exclude {int set; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_walk_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sb1250_bus_dma_mask_exclude*) ; 
 int /*<<< orphan*/  sb1250_bus_dma_mask ; 

__attribute__((used)) static void quirk_sb1250_pci_dac(struct pci_dev *dev)
{
	struct sb1250_bus_dma_mask_exclude exclude = { .set = false };

	pci_walk_bus(dev->bus, sb1250_bus_dma_mask, &exclude);
}