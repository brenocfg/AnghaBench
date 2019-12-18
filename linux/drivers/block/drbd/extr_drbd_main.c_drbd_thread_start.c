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
struct task_struct {int dummy; } ;
struct drbd_thread {int t_state; int reset_cpu_mask; int /*<<< orphan*/  t_lock; int /*<<< orphan*/ * name; struct task_struct* task; TYPE_1__* connection; struct drbd_resource* resource; int /*<<< orphan*/  stop; } ;
struct drbd_resource {int /*<<< orphan*/  kref; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_4__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
#define  EXITING 131 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
#define  NONE 130 
#define  RESTARTING 129 
#define  RUNNING 128 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int /*<<< orphan*/  drbd_destroy_resource ; 
 int /*<<< orphan*/  drbd_err (struct drbd_resource*,char*) ; 
 int /*<<< orphan*/  drbd_info (struct drbd_resource*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_thread_setup ; 
 int /*<<< orphan*/  flush_signals (TYPE_2__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int drbd_thread_start(struct drbd_thread *thi)
{
	struct drbd_resource *resource = thi->resource;
	struct task_struct *nt;
	unsigned long flags;

	/* is used from state engine doing drbd_thread_stop_nowait,
	 * while holding the req lock irqsave */
	spin_lock_irqsave(&thi->t_lock, flags);

	switch (thi->t_state) {
	case NONE:
		drbd_info(resource, "Starting %s thread (from %s [%d])\n",
			 thi->name, current->comm, current->pid);

		/* Get ref on module for thread - this is released when thread exits */
		if (!try_module_get(THIS_MODULE)) {
			drbd_err(resource, "Failed to get module reference in drbd_thread_start\n");
			spin_unlock_irqrestore(&thi->t_lock, flags);
			return false;
		}

		kref_get(&resource->kref);
		if (thi->connection)
			kref_get(&thi->connection->kref);

		init_completion(&thi->stop);
		thi->reset_cpu_mask = 1;
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		flush_signals(current); /* otherw. may get -ERESTARTNOINTR */

		nt = kthread_create(drbd_thread_setup, (void *) thi,
				    "drbd_%c_%s", thi->name[0], thi->resource->name);

		if (IS_ERR(nt)) {
			drbd_err(resource, "Couldn't start thread\n");

			if (thi->connection)
				kref_put(&thi->connection->kref, drbd_destroy_connection);
			kref_put(&resource->kref, drbd_destroy_resource);
			module_put(THIS_MODULE);
			return false;
		}
		spin_lock_irqsave(&thi->t_lock, flags);
		thi->task = nt;
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		wake_up_process(nt);
		break;
	case EXITING:
		thi->t_state = RESTARTING;
		drbd_info(resource, "Restarting %s thread (from %s [%d])\n",
				thi->name, current->comm, current->pid);
		/* fall through */
	case RUNNING:
	case RESTARTING:
	default:
		spin_unlock_irqrestore(&thi->t_lock, flags);
		break;
	}

	return true;
}