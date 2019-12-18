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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bhnd_resource {int dummy; } ;
struct bcma_devinfo {struct bhnd_resource* res_agent; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_DMP_IOCTRL ; 
 int BCMA_DMP_IOCTRL_MASK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int bhnd_bus_read_4 (struct bhnd_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_bus_write_4 (struct bhnd_resource*,int /*<<< orphan*/ ,int) ; 
 struct bcma_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 

__attribute__((used)) static int
bcma_write_ioctl(device_t dev, device_t child, uint16_t value, uint16_t mask)
{
	struct bcma_devinfo	*dinfo;
	struct bhnd_resource	*r;
	uint32_t		 ioctl;

	if (device_get_parent(child) != dev)
		return (EINVAL);

	dinfo = device_get_ivars(child);
	if ((r = dinfo->res_agent) == NULL)
		return (ENODEV);

	/* Write new value */
	ioctl = bhnd_bus_read_4(r, BCMA_DMP_IOCTRL);
	ioctl &= ~(BCMA_DMP_IOCTRL_MASK & mask);
	ioctl |= (value & mask);

	bhnd_bus_write_4(r, BCMA_DMP_IOCTRL, ioctl);

	/* Perform read-back and wait for completion */
	bhnd_bus_read_4(r, BCMA_DMP_IOCTRL);
	DELAY(10);

	return (0);
}