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
struct ntb_pci_bar_info {int /*<<< orphan*/  pci_resource; int /*<<< orphan*/  vbase; int /*<<< orphan*/  size; int /*<<< orphan*/  pbase; int /*<<< orphan*/  pci_bus_handle; int /*<<< orphan*/  pci_bus_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_virtual (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
save_bar_parameters(struct ntb_pci_bar_info *bar)
{

	bar->pci_bus_tag = rman_get_bustag(bar->pci_resource);
	bar->pci_bus_handle = rman_get_bushandle(bar->pci_resource);
	bar->pbase = rman_get_start(bar->pci_resource);
	bar->size = rman_get_size(bar->pci_resource);
	bar->vbase = rman_get_virtual(bar->pci_resource);
}