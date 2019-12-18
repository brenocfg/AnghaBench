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
struct inode {int /*<<< orphan*/  i_mode; struct binder_device* i_private; } ;
struct binderfs_info {int /*<<< orphan*/  device_count; } ;
struct TYPE_3__ {struct binder_device* name; } ;
struct TYPE_4__ {int /*<<< orphan*/  minor; } ;
struct binder_device {TYPE_1__ context; TYPE_2__ miscdev; } ;

/* Variables and functions */
 struct binderfs_info* BINDERFS_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binderfs_minors ; 
 int /*<<< orphan*/  binderfs_minors_mutex ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct binder_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binderfs_evict_inode(struct inode *inode)
{
	struct binder_device *device = inode->i_private;
	struct binderfs_info *info = BINDERFS_I(inode);

	clear_inode(inode);

	if (!S_ISCHR(inode->i_mode) || !device)
		return;

	mutex_lock(&binderfs_minors_mutex);
	--info->device_count;
	ida_free(&binderfs_minors, device->miscdev.minor);
	mutex_unlock(&binderfs_minors_mutex);

	kfree(device->context.name);
	kfree(device);
}