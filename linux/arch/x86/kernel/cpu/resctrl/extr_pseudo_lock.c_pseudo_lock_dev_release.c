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
struct rdtgroup {int /*<<< orphan*/  waitcount; } ;
struct inode {int dummy; } ;
struct file {struct rdtgroup* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 

__attribute__((used)) static int pseudo_lock_dev_release(struct inode *inode, struct file *filp)
{
	struct rdtgroup *rdtgrp;

	mutex_lock(&rdtgroup_mutex);
	rdtgrp = filp->private_data;
	WARN_ON(!rdtgrp);
	if (!rdtgrp) {
		mutex_unlock(&rdtgroup_mutex);
		return -ENODEV;
	}
	filp->private_data = NULL;
	atomic_dec(&rdtgrp->waitcount);
	mutex_unlock(&rdtgroup_mutex);
	return 0;
}