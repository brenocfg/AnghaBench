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
struct amd_ntb_softc {int /*<<< orphan*/  device; } ;
struct amd_ntb_pci_bar_info {int /*<<< orphan*/ * pci_resource; int /*<<< orphan*/  pci_resource_id; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_map_success (struct amd_ntb_softc*,struct amd_ntb_pci_bar_info*,char*) ; 
 int /*<<< orphan*/  save_bar_parameters (struct amd_ntb_pci_bar_info*) ; 

__attribute__((used)) static int
map_bar(struct amd_ntb_softc *ntb, struct amd_ntb_pci_bar_info *bar)
{
	bar->pci_resource = bus_alloc_resource_any(ntb->device, SYS_RES_MEMORY,
	    &bar->pci_resource_id, RF_ACTIVE);
	if (bar->pci_resource == NULL)
		return (ENXIO);

	save_bar_parameters(bar);
	print_map_success(ntb, bar, "mmr");

	return (0);
}