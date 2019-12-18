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
struct bhnd_pcie2_devinfo {int /*<<< orphan*/  resources; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct bhnd_pcie2_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  device_set_ivars (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct bhnd_pcie2_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bhnd_pcie2_child_deleted(device_t dev, device_t child)
{
	struct bhnd_pcie2_devinfo *dinfo;

	if (device_get_parent(child) != dev)
		return;

	dinfo = device_get_ivars(child);
	if (dinfo != NULL) {
		resource_list_free(&dinfo->resources);
		free(dinfo, M_DEVBUF);
	}

	device_set_ivars(child, NULL);
}