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
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  IIC_RELEASE_BUS 129 
#define  IIC_REQUEST_BUS 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpbb_callback(device_t dev, int index, caddr_t data)
{
	device_t ppbus = device_get_parent(dev);
	int error = 0;
	int how;

	switch (index) {
	case IIC_REQUEST_BUS:
		/* request the ppbus */
		how = *(int *)data;
		ppb_lock(ppbus);
		error = ppb_request_bus(ppbus, dev, how);
		ppb_unlock(ppbus);
		break;

	case IIC_RELEASE_BUS:
		/* release the ppbus */
		ppb_lock(ppbus);
		error = ppb_release_bus(ppbus, dev);
		ppb_unlock(ppbus);
		break;

	default:
		error = EINVAL;
	}

	return (error);
}