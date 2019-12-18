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
typedef  int u_int ;
struct thread {struct proc* td_proc; } ;
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;
struct proc {int dummy; } ;
struct linux_rlimit64 {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;
struct linux_prlimit64_args {size_t resource; scalar_t__ pid; int /*<<< orphan*/ * new; int /*<<< orphan*/ * old; } ;
typedef  int /*<<< orphan*/  nrlim ;
typedef  int /*<<< orphan*/  lrlim ;

/* Variables and functions */
 int EINVAL ; 
 void* LINUX_RLIM_INFINITY ; 
 size_t LINUX_RLIM_NLIMITS ; 
 int PGET_CANDEBUG ; 
 int PGET_CANSEE ; 
 int PGET_HOLD ; 
 int PGET_NOTWEXIT ; 
 int /*<<< orphan*/  PHOLD (struct proc*) ; 
 int /*<<< orphan*/  PRELE (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ RLIM_INFINITY ; 
 int copyin (int /*<<< orphan*/ *,struct rlimit*,int) ; 
 int copyout (struct linux_rlimit64*,int /*<<< orphan*/ *,int) ; 
 int kern_proc_setrlimit (struct thread*,struct proc*,int,struct rlimit*) ; 
 int /*<<< orphan*/  lim_rlimit_proc (struct proc*,int,struct rlimit*) ; 
 int* linux_to_bsd_resource ; 
 int pget (scalar_t__,int,struct proc**) ; 

int
linux_prlimit64(struct thread *td, struct linux_prlimit64_args *args)
{
	struct rlimit rlim, nrlim;
	struct linux_rlimit64 lrlim;
	struct proc *p;
	u_int which;
	int flags;
	int error;

	if (args->resource >= LINUX_RLIM_NLIMITS)
		return (EINVAL);

	which = linux_to_bsd_resource[args->resource];
	if (which == -1)
		return (EINVAL);

	if (args->new != NULL) {
		/*
		 * Note. Unlike FreeBSD where rlim is signed 64-bit Linux
		 * rlim is unsigned 64-bit. FreeBSD treats negative limits
		 * as INFINITY so we do not need a conversion even.
		 */
		error = copyin(args->new, &nrlim, sizeof(nrlim));
		if (error != 0)
			return (error);
	}

	flags = PGET_HOLD | PGET_NOTWEXIT;
	if (args->new != NULL)
		flags |= PGET_CANDEBUG;
	else
		flags |= PGET_CANSEE;
	if (args->pid == 0) {
		p = td->td_proc;
		PHOLD(p);
	} else {
		error = pget(args->pid, flags, &p);
		if (error != 0)
			return (error);
	}
	if (args->old != NULL) {
		PROC_LOCK(p);
		lim_rlimit_proc(p, which, &rlim);
		PROC_UNLOCK(p);
		if (rlim.rlim_cur == RLIM_INFINITY)
			lrlim.rlim_cur = LINUX_RLIM_INFINITY;
		else
			lrlim.rlim_cur = rlim.rlim_cur;
		if (rlim.rlim_max == RLIM_INFINITY)
			lrlim.rlim_max = LINUX_RLIM_INFINITY;
		else
			lrlim.rlim_max = rlim.rlim_max;
		error = copyout(&lrlim, args->old, sizeof(lrlim));
		if (error != 0)
			goto out;
	}

	if (args->new != NULL)
		error = kern_proc_setrlimit(td, p, which, &nrlim);

 out:
	PRELE(p);
	return (error);
}