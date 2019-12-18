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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 int OF_finddevice (char*) ; 

__attribute__((used)) static int
chrp_probe(platform_t plat)
{
	if (OF_finddevice("/memory") != -1 || OF_finddevice("/memory@0") != -1)
		return (BUS_PROBE_GENERIC);

	return (ENXIO);
}