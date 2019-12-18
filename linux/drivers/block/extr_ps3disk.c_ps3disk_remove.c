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
struct ps3disk_private {int /*<<< orphan*/  gendisk; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  queue; } ;
struct ps3_system_bus_device {int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;
struct ps3_storage_device {struct ps3disk_private* bounce_buf; TYPE_1__ sbd; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 int PS3DISK_MINORS ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disk_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ps3disk_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ps3disk_private* ps3_system_bus_get_drvdata (TYPE_1__*) ; 
 int /*<<< orphan*/  ps3_system_bus_set_drvdata (struct ps3_system_bus_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps3disk_mask ; 
 int /*<<< orphan*/  ps3disk_mask_mutex ; 
 int /*<<< orphan*/  ps3disk_sync_cache (struct ps3_storage_device*) ; 
 int /*<<< orphan*/  ps3stor_teardown (struct ps3_storage_device*) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 
 struct ps3_storage_device* to_ps3_storage_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ps3disk_remove(struct ps3_system_bus_device *_dev)
{
	struct ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	struct ps3disk_private *priv = ps3_system_bus_get_drvdata(&dev->sbd);

	mutex_lock(&ps3disk_mask_mutex);
	__clear_bit(MINOR(disk_devt(priv->gendisk)) / PS3DISK_MINORS,
		    &ps3disk_mask);
	mutex_unlock(&ps3disk_mask_mutex);
	del_gendisk(priv->gendisk);
	blk_cleanup_queue(priv->queue);
	blk_mq_free_tag_set(&priv->tag_set);
	put_disk(priv->gendisk);
	dev_notice(&dev->sbd.core, "Synchronizing disk cache\n");
	ps3disk_sync_cache(dev);
	ps3stor_teardown(dev);
	kfree(dev->bounce_buf);
	kfree(priv);
	ps3_system_bus_set_drvdata(_dev, NULL);
	return 0;
}