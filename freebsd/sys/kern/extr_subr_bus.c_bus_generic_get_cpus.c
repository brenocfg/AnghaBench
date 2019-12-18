#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpu_sets { ____Placeholder_cpu_sets } cpu_sets ;
typedef  TYPE_1__* device_t ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int BUS_GET_CPUS (int /*<<< orphan*/ *,TYPE_1__*,int,size_t,int /*<<< orphan*/ *) ; 
 int EINVAL ; 

int
bus_generic_get_cpus(device_t dev, device_t child, enum cpu_sets op,
    size_t setsize, cpuset_t *cpuset)
{

	/* Propagate up the bus hierarchy until someone handles it. */
	if (dev->parent != NULL)
		return (BUS_GET_CPUS(dev->parent, child, op, setsize, cpuset));
	return (EINVAL);
}