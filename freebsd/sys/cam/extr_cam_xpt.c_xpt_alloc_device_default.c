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
struct cam_et {int dummy; } ;
struct cam_ed {int mintags; int maxtags; } ;
struct cam_eb {int dummy; } ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
 struct cam_ed* xpt_alloc_device (struct cam_eb*,struct cam_et*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cam_ed *
xpt_alloc_device_default(struct cam_eb *bus, struct cam_et *target,
			 lun_id_t lun_id)
{
	struct cam_ed *device;

	device = xpt_alloc_device(bus, target, lun_id);
	if (device == NULL)
		return (NULL);

	device->mintags = 1;
	device->maxtags = 1;
	return (device);
}