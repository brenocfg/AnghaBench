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
struct drbd_thread {int* name; int (* function ) (struct drbd_thread*) ;scalar_t__ t_state; TYPE_1__* connection; int /*<<< orphan*/  t_lock; int /*<<< orphan*/  stop; int /*<<< orphan*/ * task; struct drbd_resource* resource; } ;
struct drbd_resource {char* name; int /*<<< orphan*/  kref; } ;
struct TYPE_4__ {int* comm; } ;
struct TYPE_3__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRBD_SIGKILL ; 
 scalar_t__ NONE ; 
 scalar_t__ RESTARTING ; 
 scalar_t__ RUNNING ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  allow_kernel_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int /*<<< orphan*/  drbd_destroy_resource ; 
 int /*<<< orphan*/  drbd_info (struct drbd_resource*,char*,int*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  snprintf (int*,int,char*,int,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct drbd_thread*) ; 

__attribute__((used)) static int drbd_thread_setup(void *arg)
{
	struct drbd_thread *thi = (struct drbd_thread *) arg;
	struct drbd_resource *resource = thi->resource;
	unsigned long flags;
	int retval;

	snprintf(current->comm, sizeof(current->comm), "drbd_%c_%s",
		 thi->name[0],
		 resource->name);

	allow_kernel_signal(DRBD_SIGKILL);
	allow_kernel_signal(SIGXCPU);
restart:
	retval = thi->function(thi);

	spin_lock_irqsave(&thi->t_lock, flags);

	/* if the receiver has been "EXITING", the last thing it did
	 * was set the conn state to "StandAlone",
	 * if now a re-connect request comes in, conn state goes C_UNCONNECTED,
	 * and receiver thread will be "started".
	 * drbd_thread_start needs to set "RESTARTING" in that case.
	 * t_state check and assignment needs to be within the same spinlock,
	 * so either thread_start sees EXITING, and can remap to RESTARTING,
	 * or thread_start see NONE, and can proceed as normal.
	 */

	if (thi->t_state == RESTARTING) {
		drbd_info(resource, "Restarting %s thread\n", thi->name);
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		goto restart;
	}

	thi->task = NULL;
	thi->t_state = NONE;
	smp_mb();
	complete_all(&thi->stop);
	spin_unlock_irqrestore(&thi->t_lock, flags);

	drbd_info(resource, "Terminating %s\n", current->comm);

	/* Release mod reference taken when thread was started */

	if (thi->connection)
		kref_put(&thi->connection->kref, drbd_destroy_connection);
	kref_put(&resource->kref, drbd_destroy_resource);
	module_put(THIS_MODULE);
	return retval;
}