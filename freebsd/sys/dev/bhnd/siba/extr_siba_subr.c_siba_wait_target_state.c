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
typedef  int uint32_t ;
typedef  int u_int ;
struct siba_devinfo {struct bhnd_resource** cfg_res; } ;
struct bhnd_resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int bhnd_bus_read_4 (struct bhnd_resource*,int /*<<< orphan*/ ) ; 

int
siba_wait_target_state(device_t dev, struct siba_devinfo *dinfo, bus_size_t reg,
    uint32_t value, uint32_t mask, u_int usec)
{
	struct bhnd_resource	*r;
	uint32_t		 rval;

	if ((r = dinfo->cfg_res[0]) == NULL)
		return (ENODEV);

	value &= mask;
	for (int i = 0; i < usec; i += 10) {
		rval = bhnd_bus_read_4(r, reg);
		if ((rval & mask) == value)
			return (0);

		DELAY(10);
	}

	return (ETIMEDOUT);
}