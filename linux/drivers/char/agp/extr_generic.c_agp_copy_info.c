#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct agp_kern_info {int mode; unsigned long page_mask; int /*<<< orphan*/  vm_ops; int /*<<< orphan*/  cant_use_aperture; int /*<<< orphan*/  current_memory; int /*<<< orphan*/  max_memory; int /*<<< orphan*/  aper_size; int /*<<< orphan*/  aper_base; int /*<<< orphan*/  device; int /*<<< orphan*/  chipset; TYPE_1__ version; } ;
struct agp_bridge_data {int mode; int /*<<< orphan*/  vm_ops; TYPE_3__* driver; int /*<<< orphan*/  current_memory_agp; int /*<<< orphan*/  max_memory_agp; int /*<<< orphan*/  gart_bus_addr; int /*<<< orphan*/  dev; TYPE_2__* version; } ;
struct TYPE_6__ {int /*<<< orphan*/  cant_use_aperture; } ;
struct TYPE_5__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int AGP2_RESERVED_MASK ; 
 int AGP3_RESERVED_MASK ; 
 int AGPSTAT_MODE_3_0 ; 
 int EIO ; 
 int /*<<< orphan*/  NOT_SUPPORTED ; 
 int /*<<< orphan*/  SUPPORTED ; 
 int /*<<< orphan*/  agp_return_size () ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct agp_kern_info*,int /*<<< orphan*/ ,int) ; 

int agp_copy_info(struct agp_bridge_data *bridge, struct agp_kern_info *info)
{
	memset(info, 0, sizeof(struct agp_kern_info));
	if (!bridge) {
		info->chipset = NOT_SUPPORTED;
		return -EIO;
	}

	info->version.major = bridge->version->major;
	info->version.minor = bridge->version->minor;
	info->chipset = SUPPORTED;
	info->device = bridge->dev;
	if (bridge->mode & AGPSTAT_MODE_3_0)
		info->mode = bridge->mode & ~AGP3_RESERVED_MASK;
	else
		info->mode = bridge->mode & ~AGP2_RESERVED_MASK;
	info->aper_base = bridge->gart_bus_addr;
	info->aper_size = agp_return_size();
	info->max_memory = bridge->max_memory_agp;
	info->current_memory = atomic_read(&bridge->current_memory_agp);
	info->cant_use_aperture = bridge->driver->cant_use_aperture;
	info->vm_ops = bridge->vm_ops;
	info->page_mask = ~0UL;
	return 0;
}