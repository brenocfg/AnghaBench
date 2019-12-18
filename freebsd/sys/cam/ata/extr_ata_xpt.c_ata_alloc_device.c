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
struct cam_ed {scalar_t__ serial_num_len; int /*<<< orphan*/ * serial_num; scalar_t__ queue_flags; scalar_t__ inq_flags; int /*<<< orphan*/  inq_data; scalar_t__ maxtags; scalar_t__ mintags; void* quirk; } ;
struct cam_eb {int dummy; } ;
struct ata_quirk_entry {int dummy; } ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
 struct ata_quirk_entry* ata_quirk_table ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int nitems (struct ata_quirk_entry*) ; 
 struct cam_ed* xpt_alloc_device (struct cam_eb*,struct cam_et*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cam_ed *
ata_alloc_device(struct cam_eb *bus, struct cam_et *target, lun_id_t lun_id)
{
	struct ata_quirk_entry *quirk;
	struct cam_ed *device;

	device = xpt_alloc_device(bus, target, lun_id);
	if (device == NULL)
		return (NULL);

	/*
	 * Take the default quirk entry until we have inquiry
	 * data and can determine a better quirk to use.
	 */
	quirk = &ata_quirk_table[nitems(ata_quirk_table) - 1];
	device->quirk = (void *)quirk;
	device->mintags = 0;
	device->maxtags = 0;
	bzero(&device->inq_data, sizeof(device->inq_data));
	device->inq_flags = 0;
	device->queue_flags = 0;
	device->serial_num = NULL;
	device->serial_num_len = 0;
	return (device);
}