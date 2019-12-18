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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  freq ;

/* Variables and functions */
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,void*,int) ; 

uint32_t
mpc85xx_get_platform_clock(void)
{
	phandle_t soc;
	static uint32_t freq;

	if (freq != 0)
		return (freq);

	soc = OF_finddevice("/soc");

	/* freq isn't modified on error. */
	OF_getencprop(soc, "bus-frequency", (void *)&freq, sizeof(freq));

	return (freq);
}