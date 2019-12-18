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
struct task_struct {int dummy; } ;
struct mm_struct {unsigned long pinned_vm; int /*<<< orphan*/  mmap_sem; } ;
struct ib_umem {unsigned long diff; int /*<<< orphan*/  work; struct mm_struct* mm; int /*<<< orphan*/  pid; struct ib_ucontext* context; scalar_t__ odp_data; } ;
struct ib_ucontext {scalar_t__ closing; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  __ib_umem_release (int /*<<< orphan*/ ,struct ib_umem*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_trylock (int /*<<< orphan*/ *) ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  ib_umem_account ; 
 unsigned long ib_umem_num_pages (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_odp_release (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_wq ; 
 int /*<<< orphan*/  kfree (struct ib_umem*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ib_umem_release(struct ib_umem *umem)
{
	struct ib_ucontext *context = umem->context;
	struct mm_struct *mm;
	struct task_struct *task;
	unsigned long diff;

	if (umem->odp_data) {
		ib_umem_odp_release(umem);
		return;
	}

	__ib_umem_release(umem->context->device, umem, 1);

	task = get_pid_task(umem->pid, PIDTYPE_PID);
	put_pid(umem->pid);
	if (!task)
		goto out;
	mm = get_task_mm(task);
	put_task_struct(task);
	if (!mm)
		goto out;

	diff = ib_umem_num_pages(umem);

	/*
	 * We may be called with the mm's mmap_sem already held.  This
	 * can happen when a userspace munmap() is the call that drops
	 * the last reference to our file and calls our release
	 * method.  If there are memory regions to destroy, we'll end
	 * up here and not be able to take the mmap_sem.  In that case
	 * we defer the vm_locked accounting to the system workqueue.
	 */
	if (context->closing) {
		if (!down_write_trylock(&mm->mmap_sem)) {
			INIT_WORK(&umem->work, ib_umem_account);
			umem->mm   = mm;
			umem->diff = diff;

			queue_work(ib_wq, &umem->work);
			return;
		}
	} else
		down_write(&mm->mmap_sem);

	mm->pinned_vm -= diff;
	up_write(&mm->mmap_sem);
	mmput(mm);
out:
	kfree(umem);
}