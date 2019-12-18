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
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  agp_devclass ; 
 scalar_t__ devclass_get_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

device_t
agp_find_device()
{
	device_t *children, child;
	int i, count;

	if (!agp_devclass)
		return NULL;
	if (devclass_get_devices(agp_devclass, &children, &count) != 0)
		return NULL;
	child = NULL;
	for (i = 0; i < count; i++) {
		if (device_is_attached(children[i])) {
			child = children[i];
			break;
		}
	}
	free(children, M_TEMP);
	return child;
}