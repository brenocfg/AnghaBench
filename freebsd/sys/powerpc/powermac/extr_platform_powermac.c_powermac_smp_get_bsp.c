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
struct cpuref {int dummy; } ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  inst ;
typedef  int /*<<< orphan*/  ihandle_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,int /*<<< orphan*/ *,int) ; 
 int OF_instance_to_package (int /*<<< orphan*/ ) ; 
 int powermac_smp_fill_cpuref (struct cpuref*,int) ; 

__attribute__((used)) static int
powermac_smp_get_bsp(platform_t plat, struct cpuref *cpuref)
{
	ihandle_t inst;
	phandle_t bsp, chosen;
	int res;

	chosen = OF_finddevice("/chosen");
	if (chosen == -1)
		return (ENXIO);

	res = OF_getprop(chosen, "cpu", &inst, sizeof(inst));
	if (res < 0)
		return (ENXIO);

	bsp = OF_instance_to_package(inst);
	return (powermac_smp_fill_cpuref(cpuref, bsp));
}