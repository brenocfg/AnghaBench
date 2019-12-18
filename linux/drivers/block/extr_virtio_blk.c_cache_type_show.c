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
typedef  size_t u8 ;
struct virtio_blk {int /*<<< orphan*/  vdev; } ;
struct gendisk {struct virtio_blk* private_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char** virtblk_cache_types ; 
 size_t virtblk_get_cache_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
cache_type_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct gendisk *disk = dev_to_disk(dev);
	struct virtio_blk *vblk = disk->private_data;
	u8 writeback = virtblk_get_cache_mode(vblk->vdev);

	BUG_ON(writeback >= ARRAY_SIZE(virtblk_cache_types));
	return snprintf(buf, 40, "%s\n", virtblk_cache_types[writeback]);
}