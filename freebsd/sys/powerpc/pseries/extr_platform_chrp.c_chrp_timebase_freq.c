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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  ticks ;
struct cpuref {int dummy; } ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int phandle_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int OF_child (int) ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,scalar_t__*,int) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int OF_peer (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static u_long
chrp_timebase_freq(platform_t plat, struct cpuref *cpuref)
{
	phandle_t cpus, cpunode;
	int32_t ticks = -1;
	int res;
	char buf[8];

	cpus = OF_finddevice("/cpus");
	if (cpus == -1)
		panic("CPU tree not found on Open Firmware\n");

	for (cpunode = OF_child(cpus); cpunode != 0; cpunode = OF_peer(cpunode)) {
		res = OF_getprop(cpunode, "device_type", buf, sizeof(buf));
		if (res > 0 && strcmp(buf, "cpu") == 0)
			break;
	}
	if (cpunode <= 0)
		panic("CPU node not found on Open Firmware\n");

	OF_getencprop(cpunode, "timebase-frequency", &ticks, sizeof(ticks));

	if (ticks <= 0)
		panic("Unable to determine timebase frequency!");

	return (ticks);
}