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
struct task_struct {int dummy; } ;
struct rdtgroup {int flags; int /*<<< orphan*/  closid; int /*<<< orphan*/  mode; TYPE_1__* kn; struct pseudo_lock_region* plr; } ;
struct pseudo_lock_region {int thread_done; unsigned int minor; int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  lock_thread_wq; int /*<<< orphan*/  cpu; } ;
typedef  struct task_struct device ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 int PTR_ERR (struct task_struct*) ; 
 int RDT_DELETED ; 
 int /*<<< orphan*/  RDT_MODE_PSEUDO_LOCKED ; 
 int /*<<< orphan*/  closid_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct rdtgroup*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_resctrl ; 
 struct task_struct* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rdtgroup*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_bind (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_create_on_node (int /*<<< orphan*/ ,struct rdtgroup*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseudo_lock_class ; 
 int pseudo_lock_cstates_constrain (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  pseudo_lock_cstates_relax (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  pseudo_lock_fn ; 
 int /*<<< orphan*/  pseudo_lock_major ; 
 int pseudo_lock_minor_get (unsigned int*) ; 
 int /*<<< orphan*/  pseudo_lock_minor_release (unsigned int) ; 
 int pseudo_lock_region_alloc (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  pseudo_lock_region_clear (struct pseudo_lock_region*) ; 
 int /*<<< orphan*/  pseudo_measure_fops ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,int) ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 int /*<<< orphan*/  rdtgroup_kn_mode_restore (struct rdtgroup*,char*,int) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int rdtgroup_pseudo_lock_create(struct rdtgroup *rdtgrp)
{
	struct pseudo_lock_region *plr = rdtgrp->plr;
	struct task_struct *thread;
	unsigned int new_minor;
	struct device *dev;
	int ret;

	ret = pseudo_lock_region_alloc(plr);
	if (ret < 0)
		return ret;

	ret = pseudo_lock_cstates_constrain(plr);
	if (ret < 0) {
		ret = -EINVAL;
		goto out_region;
	}

	plr->thread_done = 0;

	thread = kthread_create_on_node(pseudo_lock_fn, rdtgrp,
					cpu_to_node(plr->cpu),
					"pseudo_lock/%u", plr->cpu);
	if (IS_ERR(thread)) {
		ret = PTR_ERR(thread);
		rdt_last_cmd_printf("Locking thread returned error %d\n", ret);
		goto out_cstates;
	}

	kthread_bind(thread, plr->cpu);
	wake_up_process(thread);

	ret = wait_event_interruptible(plr->lock_thread_wq,
				       plr->thread_done == 1);
	if (ret < 0) {
		/*
		 * If the thread does not get on the CPU for whatever
		 * reason and the process which sets up the region is
		 * interrupted then this will leave the thread in runnable
		 * state and once it gets on the CPU it will derefence
		 * the cleared, but not freed, plr struct resulting in an
		 * empty pseudo-locking loop.
		 */
		rdt_last_cmd_puts("Locking thread interrupted\n");
		goto out_cstates;
	}

	ret = pseudo_lock_minor_get(&new_minor);
	if (ret < 0) {
		rdt_last_cmd_puts("Unable to obtain a new minor number\n");
		goto out_cstates;
	}

	/*
	 * Unlock access but do not release the reference. The
	 * pseudo-locked region will still be here on return.
	 *
	 * The mutex has to be released temporarily to avoid a potential
	 * deadlock with the mm->mmap_sem semaphore which is obtained in
	 * the device_create() and debugfs_create_dir() callpath below
	 * as well as before the mmap() callback is called.
	 */
	mutex_unlock(&rdtgroup_mutex);

	if (!IS_ERR_OR_NULL(debugfs_resctrl)) {
		plr->debugfs_dir = debugfs_create_dir(rdtgrp->kn->name,
						      debugfs_resctrl);
		if (!IS_ERR_OR_NULL(plr->debugfs_dir))
			debugfs_create_file("pseudo_lock_measure", 0200,
					    plr->debugfs_dir, rdtgrp,
					    &pseudo_measure_fops);
	}

	dev = device_create(pseudo_lock_class, NULL,
			    MKDEV(pseudo_lock_major, new_minor),
			    rdtgrp, "%s", rdtgrp->kn->name);

	mutex_lock(&rdtgroup_mutex);

	if (IS_ERR(dev)) {
		ret = PTR_ERR(dev);
		rdt_last_cmd_printf("Failed to create character device: %d\n",
				    ret);
		goto out_debugfs;
	}

	/* We released the mutex - check if group was removed while we did so */
	if (rdtgrp->flags & RDT_DELETED) {
		ret = -ENODEV;
		goto out_device;
	}

	plr->minor = new_minor;

	rdtgrp->mode = RDT_MODE_PSEUDO_LOCKED;
	closid_free(rdtgrp->closid);
	rdtgroup_kn_mode_restore(rdtgrp, "cpus", 0444);
	rdtgroup_kn_mode_restore(rdtgrp, "cpus_list", 0444);

	ret = 0;
	goto out;

out_device:
	device_destroy(pseudo_lock_class, MKDEV(pseudo_lock_major, new_minor));
out_debugfs:
	debugfs_remove_recursive(plr->debugfs_dir);
	pseudo_lock_minor_release(new_minor);
out_cstates:
	pseudo_lock_cstates_relax(plr);
out_region:
	pseudo_lock_region_clear(plr);
out:
	return ret;
}