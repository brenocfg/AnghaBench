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
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int BUS_GET_CPUS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

int
bus_get_cpus(device_t dev, enum cpu_sets op, size_t setsize, cpuset_t *cpuset)
{
	device_t parent;

	parent = device_get_parent(dev);
	if (parent == NULL)
		return (EINVAL);
	return (BUS_GET_CPUS(parent, dev, op, setsize, cpuset));
}