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
struct fsl_mc_device {int dummy; } ;
struct fsl_mc_bus {int /*<<< orphan*/  scan_mutex; } ;

/* Variables and functions */
 int dprc_scan_objects (struct fsl_mc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_cleanup_all_resource_pools (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_init_all_resource_pools (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fsl_mc_bus* to_fsl_mc_bus (struct fsl_mc_device*) ; 

__attribute__((used)) static int dprc_scan_container(struct fsl_mc_device *mc_bus_dev)
{
	int error;
	struct fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_bus_dev);

	fsl_mc_init_all_resource_pools(mc_bus_dev);

	/*
	 * Discover objects in the DPRC:
	 */
	mutex_lock(&mc_bus->scan_mutex);
	error = dprc_scan_objects(mc_bus_dev, NULL);
	mutex_unlock(&mc_bus->scan_mutex);
	if (error < 0) {
		fsl_mc_cleanup_all_resource_pools(mc_bus_dev);
		return error;
	}

	return 0;
}