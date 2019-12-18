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
struct sta2x11_mapping {scalar_t__ amba_base; } ;
struct pci_dev {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 struct sta2x11_mapping* sta2x11_pdev_to_mapping (struct pci_dev*) ; 

__attribute__((used)) static dma_addr_t a2p(dma_addr_t a, struct pci_dev *pdev)
{
	struct sta2x11_mapping *map;
	dma_addr_t p;

	map = sta2x11_pdev_to_mapping(pdev);
	p = a - map->amba_base;
	return p;
}