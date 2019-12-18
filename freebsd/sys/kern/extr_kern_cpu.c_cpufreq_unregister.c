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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ CPUFREQ_DRV_TYPE (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int
cpufreq_unregister(device_t dev)
{
	device_t cf_dev, *devs;
	int cfcount, devcount, error, i, type;

	/*
	 * If this is the last cpufreq child device, remove the control
	 * device as well.  We identify cpufreq children by calling a method
	 * they support.
	 */
	error = device_get_children(device_get_parent(dev), &devs, &devcount);
	if (error)
		return (error);
	cf_dev = device_find_child(device_get_parent(dev), "cpufreq", -1);
	if (cf_dev == NULL) {
		device_printf(dev,
	"warning: cpufreq_unregister called with no cpufreq device active\n");
		free(devs, M_TEMP);
		return (0);
	}
	cfcount = 0;
	for (i = 0; i < devcount; i++) {
		if (!device_is_attached(devs[i]))
			continue;
		if (CPUFREQ_DRV_TYPE(devs[i], &type) == 0)
			cfcount++;
	}
	if (cfcount <= 1)
		device_delete_child(device_get_parent(cf_dev), cf_dev);
	free(devs, M_TEMP);

	return (0);
}