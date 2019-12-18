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
struct octeon_device {TYPE_1__* mem_bus_space; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pci_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int) ; 

__attribute__((used)) static inline void
lio_unmap_pci_barx(struct octeon_device *oct, int baridx)
{

	lio_dev_dbg(oct, "Freeing PCI mapped regions for Bar%d\n", baridx);

	if (oct->mem_bus_space[baridx].pci_mem != NULL) {
		bus_release_resource(oct->device, SYS_RES_MEMORY,
				     PCIR_BAR(baridx * 2),
				     oct->mem_bus_space[baridx].pci_mem);
		oct->mem_bus_space[baridx].pci_mem = NULL;
	}
}