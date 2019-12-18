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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int,char*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
riscv_timer_get_timebase(device_t dev, uint32_t *freq)
{
	phandle_t node;
	int len;

	node = OF_finddevice("/cpus");
	if (node == -1) {
		if (bootverbose)
			device_printf(dev, "Can't find cpus node.\n");
		return (ENXIO);
	}

	len = OF_getproplen(node, "timebase-frequency");
	if (len != 4) {
		if (bootverbose)
			device_printf(dev,
			    "Can't find timebase-frequency property.\n");
		return (ENXIO);
	}

	OF_getencprop(node, "timebase-frequency", freq, len);

	return (0);
}