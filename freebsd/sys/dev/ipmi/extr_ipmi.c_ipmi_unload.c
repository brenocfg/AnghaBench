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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ devclass_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipmi_devclass ; 

__attribute__((used)) static void
ipmi_unload(void *arg)
{
	device_t *	devs;
	int		count;
	int		i;

	if (ipmi_devclass == NULL)
		return;
	if (devclass_get_devices(ipmi_devclass, &devs, &count) != 0)
		return;
	for (i = 0; i < count; i++)
		device_delete_child(device_get_parent(devs[i]), devs[i]);
	free(devs, M_TEMP);
}