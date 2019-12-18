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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int32_t ;
struct agp_gatt {int ag_entries; void* ag_virtual; int /*<<< orphan*/  ag_physical; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 int AGP_PAGE_SHIFT ; 
 int /*<<< orphan*/  M_AGP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct agp_gatt*,int /*<<< orphan*/ ) ; 
 scalar_t__ kmem_alloc_contig (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct agp_gatt* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

struct agp_gatt *
agp_alloc_gatt(device_t dev)
{
	u_int32_t apsize = AGP_GET_APERTURE(dev);
	u_int32_t entries = apsize >> AGP_PAGE_SHIFT;
	struct agp_gatt *gatt;

	if (bootverbose)
		device_printf(dev,
			      "allocating GATT for aperture of size %dM\n",
			      apsize / (1024*1024));

	if (entries == 0) {
		device_printf(dev, "bad aperture size\n");
		return NULL;
	}

	gatt = malloc(sizeof(struct agp_gatt), M_AGP, M_NOWAIT);
	if (!gatt)
		return 0;

	gatt->ag_entries = entries;
	gatt->ag_virtual = (void *)kmem_alloc_contig(entries *
	    sizeof(u_int32_t), M_NOWAIT | M_ZERO, 0, ~0, PAGE_SIZE, 0,
	    VM_MEMATTR_WRITE_COMBINING);
	if (!gatt->ag_virtual) {
		if (bootverbose)
			device_printf(dev, "contiguous allocation failed\n");
		free(gatt, M_AGP);
		return 0;
	}
	gatt->ag_physical = vtophys((vm_offset_t) gatt->ag_virtual);

	return gatt;
}