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
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct gendisk {struct blkfront_info* private_data; } ;
struct block_device {int /*<<< orphan*/  bd_mutex; int /*<<< orphan*/  bd_openers; } ;
struct blkfront_info {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * xbdev; struct gendisk* gd; } ;

/* Variables and functions */
 struct block_device* bdget_disk (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  blkfront_mutex ; 
 int /*<<< orphan*/  blkif_free (struct blkfront_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct blkfront_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  free_info (struct blkfront_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlvbd_release_gendisk (struct blkfront_info*) ; 

__attribute__((used)) static int blkfront_remove(struct xenbus_device *xbdev)
{
	struct blkfront_info *info = dev_get_drvdata(&xbdev->dev);
	struct block_device *bdev = NULL;
	struct gendisk *disk;

	dev_dbg(&xbdev->dev, "%s removed", xbdev->nodename);

	if (!info)
		return 0;

	blkif_free(info, 0);

	mutex_lock(&info->mutex);

	disk = info->gd;
	if (disk)
		bdev = bdget_disk(disk, 0);

	info->xbdev = NULL;
	mutex_unlock(&info->mutex);

	if (!bdev) {
		mutex_lock(&blkfront_mutex);
		free_info(info);
		mutex_unlock(&blkfront_mutex);
		return 0;
	}

	/*
	 * The xbdev was removed before we reached the Closed
	 * state. See if it's safe to remove the disk. If the bdev
	 * isn't closed yet, we let release take care of it.
	 */

	mutex_lock(&bdev->bd_mutex);
	info = disk->private_data;

	dev_warn(disk_to_dev(disk),
		 "%s was hot-unplugged, %d stale handles\n",
		 xbdev->nodename, bdev->bd_openers);

	if (info && !bdev->bd_openers) {
		xlvbd_release_gendisk(info);
		disk->private_data = NULL;
		mutex_lock(&blkfront_mutex);
		free_info(info);
		mutex_unlock(&blkfront_mutex);
	}

	mutex_unlock(&bdev->bd_mutex);
	bdput(bdev);

	return 0;
}