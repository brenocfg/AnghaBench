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
typedef  scalar_t__ uint32_t ;
struct bcma_devinfo {int /*<<< orphan*/ * res_agent; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_DMP_RESETSTATUS ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 scalar_t__ bhnd_bus_read_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
bcma_dmp_wait_reset(device_t child, struct bcma_devinfo *dinfo)
{
	uint32_t rst;

	if (dinfo->res_agent == NULL)
		return (ENODEV);

	/* 300us should be long enough, but there are references to this
	 * requiring up to 10ms when performing reset of an 80211 core
	 * after a MAC PSM microcode watchdog event. */
	for (int i = 0; i < 10000; i += 10) {
		rst = bhnd_bus_read_4(dinfo->res_agent, BCMA_DMP_RESETSTATUS);
		if (rst == 0)
			return (0);

		DELAY(10);
	}

	device_printf(child, "BCMA_DMP_RESETSTATUS timeout\n");
	return (ETIMEDOUT);
}