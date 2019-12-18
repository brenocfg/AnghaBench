#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubd {int size; } ;
struct hd_geometry {int heads; int sectors; int cylinders; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct ubd* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int ubd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct ubd *ubd_dev = bdev->bd_disk->private_data;

	geo->heads = 128;
	geo->sectors = 32;
	geo->cylinders = ubd_dev->size / (128 * 32 * 512);
	return 0;
}