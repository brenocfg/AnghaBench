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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cell_dma_dev_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cell_pci_dma_dev_setup(struct pci_dev *dev)
{
	cell_dma_dev_setup(&dev->dev);
}