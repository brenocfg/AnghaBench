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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint32_t ;
struct siba_devinfo {struct bhnd_resource** cfg_res; } ;
struct bhnd_resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int SIBA_CFG_SIZE ; 
 int bhnd_bus_read_4 (struct bhnd_resource*,int) ; 
 int /*<<< orphan*/  bhnd_bus_write_4 (struct bhnd_resource*,int,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 

void
siba_write_target_state(device_t dev, struct siba_devinfo *dinfo,
    bus_size_t reg, uint32_t value, uint32_t mask)
{
	struct bhnd_resource	*r;
	uint32_t		 rval;

	r = dinfo->cfg_res[0];

	KASSERT(r != NULL, ("%s missing CFG0 mapping",
	    device_get_nameunit(dev)));
	KASSERT(reg <= SIBA_CFG_SIZE-4, ("%s invalid CFG0 register offset %#jx",
	    device_get_nameunit(dev), (uintmax_t)reg));

	rval = bhnd_bus_read_4(r, reg);
	rval &= ~mask;
	rval |= (value & mask);

	bhnd_bus_write_4(r, reg, rval);
	bhnd_bus_read_4(r, reg); /* read-back */
	DELAY(1);
}