#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drbd_device {TYPE_2__* this_bdev; int /*<<< orphan*/  vdisk; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;
struct TYPE_4__ {TYPE_1__* bd_inode; } ;
struct TYPE_3__ {int i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _drbd_set_my_capacity(struct drbd_device *device, sector_t size)
{
	/* set_capacity(device->this_bdev->bd_disk, size); */
	set_capacity(device->vdisk, size);
	device->this_bdev->bd_inode->i_size = (loff_t)size << 9;
}