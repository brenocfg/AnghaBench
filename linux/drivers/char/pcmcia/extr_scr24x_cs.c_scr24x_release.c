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
struct scr24x_dev {int /*<<< orphan*/  refcnt; } ;
struct inode {int dummy; } ;
struct file {struct scr24x_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr24x_delete ; 

__attribute__((used)) static int scr24x_release(struct inode *inode, struct file *filp)
{
	struct scr24x_dev *dev = filp->private_data;

	/* We must not take the dev->lock here as scr24x_delete()
	 * might be called to remove the dev structure altogether.
	 * We don't need the lock anyway, since after the reference
	 * acquired in probe() is released in remove() the chrdev
	 * is already unregistered and noone can possibly acquire
	 * a reference via open() anymore. */
	kref_put(&dev->refcnt, scr24x_delete);
	return 0;
}