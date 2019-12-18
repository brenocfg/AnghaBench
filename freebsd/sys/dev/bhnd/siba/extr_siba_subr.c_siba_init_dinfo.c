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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct siba_core_id {size_t num_admatch; int num_cfg_blocks; TYPE_1__* admatch; } ;
struct siba_devinfo {struct siba_core_id core_id; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  am_size; int /*<<< orphan*/  am_base; } ;

/* Variables and functions */
 int SIBA_CFG_SIZE ; 
 size_t SIBA_CORE_ADDRSPACE ; 
 int siba_append_dinfo_region (struct siba_devinfo*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int siba_register_interrupts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct siba_devinfo*) ; 

int
siba_init_dinfo(device_t dev, device_t child, struct siba_devinfo *dinfo,
    const struct siba_core_id *core_id)
{
	int error;

	dinfo->core_id = *core_id;

	/* Register all address space mappings */
	for (uint8_t i = 0; i < core_id->num_admatch; i++) {
		uint32_t bus_reserved;

		/* If this is the device's core/enumeration addrespace,
		 * reserve the Sonics configuration register blocks for the
		 * use of our bus. */
		bus_reserved = 0;
		if (i == SIBA_CORE_ADDRSPACE)
			bus_reserved = core_id->num_cfg_blocks * SIBA_CFG_SIZE;

		/* Append the region info */
		error = siba_append_dinfo_region(dinfo, i,
		    core_id->admatch[i].am_base, core_id->admatch[i].am_size,
		    bus_reserved);
		if (error)
			return (error);
	}

	/* Register all interrupt(s) */
	if ((error = siba_register_interrupts(dev, child, dinfo)))
		return (error);

	return (0);
}