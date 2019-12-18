#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode_data {scalar_t__ refcount; int /*<<< orphan*/  lock; TYPE_2__* mount; int /*<<< orphan*/  chain; } ;
struct TYPE_5__ {TYPE_1__* fs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* inode_orphaned ) (TYPE_2__*,struct inode_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct inode_data*) ; 
 int /*<<< orphan*/  inodes_lock ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mount_release (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct inode_data*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void inode_release(struct inode_data *inode) {
    lock(&inodes_lock);
    lock(&inode->lock);
    if (--inode->refcount == 0) {
        unlock(&inode->lock);
        list_remove(&inode->chain);
        unlock(&inodes_lock);
        if (inode->mount->fs->inode_orphaned)
            inode->mount->fs->inode_orphaned(inode->mount, inode);
        mount_release(inode->mount);
        free(inode);
    } else {
        unlock(&inode->lock);
        unlock(&inodes_lock);
    }
}