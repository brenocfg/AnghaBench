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
struct cam_ed {scalar_t__ serial_num_len; int /*<<< orphan*/ * serial_num; scalar_t__ queue_flags; scalar_t__ inq_flags; int /*<<< orphan*/  inq_data; scalar_t__ maxtags; scalar_t__ mintags; int /*<<< orphan*/ * quirk; } ;
struct cam_eb {int dummy; } ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct cam_ed* xpt_alloc_device (struct cam_eb*,struct cam_et*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cam_ed *
mmc_alloc_device(struct cam_eb *bus, struct cam_et *target, lun_id_t lun_id)
{
	struct cam_ed *device;

	printf("mmc_alloc_device()\n");
	device = xpt_alloc_device(bus, target, lun_id);
	if (device == NULL)
		return (NULL);

	device->quirk = NULL;
	device->mintags = 0;
	device->maxtags = 0;
	bzero(&device->inq_data, sizeof(device->inq_data));
	device->inq_flags = 0;
	device->queue_flags = 0;
	device->serial_num = NULL;
	device->serial_num_len = 0;
	return (device);
}