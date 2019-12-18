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
typedef  enum cpu_sets { ____Placeholder_cpu_sets } cpu_sets ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_AND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
#define  INTR_CPUS 129 
#define  LOCAL_CPUS 128 
 int acpi_parse_pxm (int /*<<< orphan*/ ) ; 
 int bus_generic_get_cpus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpuset_domain ; 

int
acpi_get_cpus(device_t dev, device_t child, enum cpu_sets op, size_t setsize,
    cpuset_t *cpuset)
{
	int d, error;

	d = acpi_parse_pxm(child);
	if (d < 0)
		return (bus_generic_get_cpus(dev, child, op, setsize, cpuset));

	switch (op) {
	case LOCAL_CPUS:
		if (setsize != sizeof(cpuset_t))
			return (EINVAL);
		*cpuset = cpuset_domain[d];
		return (0);
	case INTR_CPUS:
		error = bus_generic_get_cpus(dev, child, op, setsize, cpuset);
		if (error != 0)
			return (error);
		if (setsize != sizeof(cpuset_t))
			return (EINVAL);
		CPU_AND(cpuset, &cpuset_domain[d]);
		return (0);
	default:
		return (bus_generic_get_cpus(dev, child, op, setsize, cpuset));
	}
}