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
struct vmspace {int dummy; } ;
struct thread {int /*<<< orphan*/ * td_emuldata; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/ * p_emuldata; } ;
struct linux_pemuldata {struct linux_pemuldata* epoll; } ;
struct linux_emuldata {struct linux_emuldata* epoll; } ;
struct image_args {int dummy; } ;
struct epoll_emuldata {struct epoll_emuldata* epoll; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_EPOLL ; 
 int /*<<< orphan*/  M_LINUX ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ SV_ABI_LINUX ; 
 scalar_t__ SV_CURPROC_ABI () ; 
 struct linux_pemuldata* em_find (struct thread*) ; 
 int /*<<< orphan*/  free (struct linux_pemuldata*,int /*<<< orphan*/ ) ; 
 int kern_execve (struct thread*,struct image_args*,int /*<<< orphan*/ *) ; 
 struct linux_pemuldata* pem_find (struct proc*) ; 
 int /*<<< orphan*/  post_execve (struct thread*,int,struct vmspace*) ; 
 int pre_execve (struct thread*,struct vmspace**) ; 

int
linux_common_execve(struct thread *td, struct image_args *eargs)
{
	struct linux_pemuldata *pem;
	struct epoll_emuldata *emd;
	struct vmspace *oldvmspace;
	struct linux_emuldata *em;
	struct proc *p;
	int error;

	p = td->td_proc;

	error = pre_execve(td, &oldvmspace);
	if (error != 0)
		return (error);

	error = kern_execve(td, eargs, NULL);
	post_execve(td, error, oldvmspace);
	if (error != EJUSTRETURN)
		return (error);

	/*
	 * In a case of transition from Linux binary execing to
	 * FreeBSD binary we destroy Linux emuldata thread & proc entries.
	 */
	if (SV_CURPROC_ABI() != SV_ABI_LINUX) {
		PROC_LOCK(p);
		em = em_find(td);
		KASSERT(em != NULL, ("proc_exec: thread emuldata not found.\n"));
		td->td_emuldata = NULL;

		pem = pem_find(p);
		KASSERT(pem != NULL, ("proc_exec: proc pemuldata not found.\n"));
		p->p_emuldata = NULL;
		PROC_UNLOCK(p);

		if (pem->epoll != NULL) {
			emd = pem->epoll;
			pem->epoll = NULL;
			free(emd, M_EPOLL);
		}

		free(em, M_TEMP);
		free(pem, M_LINUX);
	}
	return (EJUSTRETURN);
}