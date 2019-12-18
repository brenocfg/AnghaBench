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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  cpufreq_register (scalar_t__) ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 int pn_decode_acpi (scalar_t__,scalar_t__) ; 
 int pn_decode_pst (scalar_t__) ; 

__attribute__((used)) static int
pn_attach(device_t dev)
{
	int rv;
	device_t child;

	child = device_find_child(device_get_parent(dev), "acpi_perf", -1);
	if (child) {
		rv = pn_decode_acpi(dev, child);
		if (rv)
			rv = pn_decode_pst(dev);
	} else
		rv = pn_decode_pst(dev);

	if (rv != 0)
		return (ENXIO);
	cpufreq_register(dev);
	return (0);
}