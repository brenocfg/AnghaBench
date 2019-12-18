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
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lebuffer_destroy_dinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lebuffer_detach(device_t dev)
{
	device_t *children;
	int i, nchildren;

	bus_generic_detach(dev);
	if (device_get_children(dev, &children, &nchildren) == 0) {
		for (i = 0; i < nchildren; i++) {
			lebuffer_destroy_dinfo(device_get_ivars(children[i]));
			device_delete_child(dev, children[i]);
		}
		free(children, M_TEMP);
	}
	return (0);
}