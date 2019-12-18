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
struct sta2x11_mapping {int amba_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_sta2x11; } ;
struct device {int* dma_mask; TYPE_1__ archdata; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int STA2X11_AMBA_SIZE ; 
 struct sta2x11_mapping* sta2x11_pdev_to_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

bool dma_capable(struct device *dev, dma_addr_t addr, size_t size)
{
	struct sta2x11_mapping *map;

	if (!dev->archdata.is_sta2x11) {
		if (!dev->dma_mask)
			return false;
		return addr + size - 1 <= *dev->dma_mask;
	}

	map = sta2x11_pdev_to_mapping(to_pci_dev(dev));

	if (!map || (addr < map->amba_base))
		return false;
	if (addr + size >= map->amba_base + STA2X11_AMBA_SIZE) {
		return false;
	}

	return true;
}