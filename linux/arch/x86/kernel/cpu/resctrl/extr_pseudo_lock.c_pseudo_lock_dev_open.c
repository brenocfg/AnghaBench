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
struct file {int f_mode; struct rdtgroup* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int FMODE_LSEEK ; 
 int FMODE_PREAD ; 
 int FMODE_PWRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 struct rdtgroup* region_find_by_minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pseudo_lock_dev_open(struct inode *inode, struct file *filp)
{
	struct rdtgroup *rdtgrp;

	mutex_lock(&rdtgroup_mutex);

	rdtgrp = region_find_by_minor(iminor(inode));
	if (!rdtgrp) {
		mutex_unlock(&rdtgroup_mutex);
		return -ENODEV;
	}

	filp->private_data = rdtgrp;
	atomic_inc(&rdtgrp->waitcount);
	/* Perform a non-seekable open - llseek is not supported */
	filp->f_mode &= ~(FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);

	mutex_unlock(&rdtgroup_mutex);

	return 0;
}