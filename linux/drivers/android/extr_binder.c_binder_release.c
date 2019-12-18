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
struct inode {int dummy; } ;
struct file {struct binder_proc* private_data; } ;
struct binder_proc {int /*<<< orphan*/ * binderfs_entry; int /*<<< orphan*/  debugfs_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEFERRED_RELEASE ; 
 int /*<<< orphan*/  binder_defer_work (struct binder_proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binderfs_remove_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binder_release(struct inode *nodp, struct file *filp)
{
	struct binder_proc *proc = filp->private_data;

	debugfs_remove(proc->debugfs_entry);

	if (proc->binderfs_entry) {
		binderfs_remove_file(proc->binderfs_entry);
		proc->binderfs_entry = NULL;
	}

	binder_defer_work(proc, BINDER_DEFERRED_RELEASE);

	return 0;
}