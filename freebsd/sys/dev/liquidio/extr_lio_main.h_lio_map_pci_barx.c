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
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  tag; int /*<<< orphan*/ * pci_mem; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LIO_CAST64 (int /*<<< orphan*/ ) ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
lio_map_pci_barx(struct octeon_device *oct, int baridx)
{
	int	rid = PCIR_BAR(baridx * 2);

	oct->mem_bus_space[baridx].pci_mem =
		bus_alloc_resource_any(oct->device, SYS_RES_MEMORY, &rid,
				       RF_ACTIVE);

	if (oct->mem_bus_space[baridx].pci_mem == NULL) {
		lio_dev_err(oct, "Unable to allocate bus resource: memory\n");
		return (ENXIO);
	}

	/* Save bus_space values for READ/WRITE_REG macros */
	oct->mem_bus_space[baridx].tag =
		rman_get_bustag(oct->mem_bus_space[baridx].pci_mem);
	oct->mem_bus_space[baridx].handle =
		rman_get_bushandle(oct->mem_bus_space[baridx].pci_mem);

	lio_dev_dbg(oct, "BAR%d Tag 0x%llx Handle 0x%llx\n",
		    baridx, LIO_CAST64(oct->mem_bus_space[baridx].tag),
		    LIO_CAST64(oct->mem_bus_space[baridx].handle));

	return (0);
}