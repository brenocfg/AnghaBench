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
struct thread {int dummy; } ;
struct msgring_thread {struct thread* thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRI_ITHD ; 
 int /*<<< orphan*/  RFSTOPPED ; 
 int /*<<< orphan*/  SRQ_INTR ; 
 int kproc_kthread_add (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,struct thread**,int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  msgring_proc ; 
 int /*<<< orphan*/  msgring_process ; 
 struct msgring_thread* msgring_threads ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  sched_add (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_class (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static void
create_msgring_thread(int hwtid)
{
	struct msgring_thread *mthd;
	struct thread *td;
	int	error;

	mthd = &msgring_threads[hwtid];
	error = kproc_kthread_add(msgring_process, (void *)(uintptr_t)hwtid,
	    &msgring_proc, &td, RFSTOPPED, 2, "msgrngproc",
	    "msgthr%d", hwtid);
	if (error)
		panic("kproc_kthread_add() failed with %d", error);
	mthd->thread = td;

	thread_lock(td);
	sched_class(td, PRI_ITHD);
	sched_add(td, SRQ_INTR);
	thread_unlock(td);
}