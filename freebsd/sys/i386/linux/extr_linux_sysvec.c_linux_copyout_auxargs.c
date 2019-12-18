#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ps_strings {int dummy; } ;
struct proc {int p_flag; TYPE_2__* p_ucred; TYPE_1__* p_sysent; } ;
struct image_params {int canary; int execpathp; int /*<<< orphan*/ * auxargs; struct proc* proc; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_6__ {int phdr; int phent; int phnum; int pagesz; int flags; int entry; int base; int execfd; } ;
struct TYPE_5__ {int cr_ruid; int cr_svuid; int cr_rgid; int cr_svgid; } ;
struct TYPE_4__ {int sv_shared_page_base; scalar_t__ sv_psstrings; } ;
typedef  int /*<<< orphan*/  Elf32_Auxinfo ;
typedef  TYPE_3__ Elf32_Auxargs ;
typedef  int /*<<< orphan*/  Elf32_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  AT_BASE ; 
 int /*<<< orphan*/  AT_EGID ; 
 int /*<<< orphan*/  AT_ENTRY ; 
 int /*<<< orphan*/  AT_EUID ; 
 int /*<<< orphan*/  AT_EXECFD ; 
 int /*<<< orphan*/  AT_FLAGS ; 
 int /*<<< orphan*/  AT_GID ; 
 int /*<<< orphan*/  AT_NULL ; 
 int /*<<< orphan*/  AT_PAGESZ ; 
 int /*<<< orphan*/  AT_PHDR ; 
 int /*<<< orphan*/  AT_PHENT ; 
 int /*<<< orphan*/  AT_PHNUM ; 
 int /*<<< orphan*/  AT_UID ; 
 int /*<<< orphan*/  AUXARGS_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LINUX_AT_CLKTCK ; 
 int LINUX_AT_COUNT ; 
 int /*<<< orphan*/  LINUX_AT_EXECFN ; 
 int /*<<< orphan*/  LINUX_AT_HWCAP ; 
 int /*<<< orphan*/  LINUX_AT_PLATFORM ; 
 int /*<<< orphan*/  LINUX_AT_RANDOM ; 
 int /*<<< orphan*/  LINUX_AT_SECURE ; 
 int /*<<< orphan*/  LINUX_AT_SYSINFO ; 
 int /*<<< orphan*/  LINUX_AT_SYSINFO_EHDR ; 
 scalar_t__ LINUX_KERNVER_2004000 ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PTROUT (int /*<<< orphan*/ *) ; 
 int P_SUGID ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,void*,int) ; 
 int cpu_feature ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ linux_kernver (int /*<<< orphan*/ ) ; 
 scalar_t__ linux_szplatform ; 
 int linux_vsyscall ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int stclohz ; 

__attribute__((used)) static void
linux_copyout_auxargs(struct image_params *imgp, u_long *base)
{
	struct proc *p;
	Elf32_Auxargs *args;
	Elf32_Auxinfo *argarray, *pos;
	Elf32_Addr *uplatform;
	struct ps_strings *arginfo;
	u_long auxlen;
	int issetugid;

	p = imgp->proc;
	issetugid = imgp->proc->p_flag & P_SUGID ? 1 : 0;
	arginfo = (struct ps_strings *)p->p_sysent->sv_psstrings;
	uplatform = (Elf32_Addr *)((caddr_t)arginfo - linux_szplatform);
	args = (Elf32_Auxargs *)imgp->auxargs;
	argarray = pos = malloc(LINUX_AT_COUNT * sizeof(*pos), M_TEMP,
	    M_WAITOK | M_ZERO);

	AUXARGS_ENTRY(pos, LINUX_AT_SYSINFO_EHDR,
	    imgp->proc->p_sysent->sv_shared_page_base);
	AUXARGS_ENTRY(pos, LINUX_AT_SYSINFO, linux_vsyscall);
	AUXARGS_ENTRY(pos, LINUX_AT_HWCAP, cpu_feature);

	/*
	 * Do not export AT_CLKTCK when emulating Linux kernel prior to 2.4.0,
	 * as it has appeared in the 2.4.0-rc7 first time.
	 * Being exported, AT_CLKTCK is returned by sysconf(_SC_CLK_TCK),
	 * glibc falls back to the hard-coded CLK_TCK value when aux entry
	 * is not present.
	 * Also see linux_times() implementation.
	 */
	if (linux_kernver(curthread) >= LINUX_KERNVER_2004000)
		AUXARGS_ENTRY(pos, LINUX_AT_CLKTCK, stclohz);
	AUXARGS_ENTRY(pos, AT_PHDR, args->phdr);
	AUXARGS_ENTRY(pos, AT_PHENT, args->phent);
	AUXARGS_ENTRY(pos, AT_PHNUM, args->phnum);
	AUXARGS_ENTRY(pos, AT_PAGESZ, args->pagesz);
	AUXARGS_ENTRY(pos, AT_FLAGS, args->flags);
	AUXARGS_ENTRY(pos, AT_ENTRY, args->entry);
	AUXARGS_ENTRY(pos, AT_BASE, args->base);
	AUXARGS_ENTRY(pos, LINUX_AT_SECURE, issetugid);
	AUXARGS_ENTRY(pos, AT_UID, imgp->proc->p_ucred->cr_ruid);
	AUXARGS_ENTRY(pos, AT_EUID, imgp->proc->p_ucred->cr_svuid);
	AUXARGS_ENTRY(pos, AT_GID, imgp->proc->p_ucred->cr_rgid);
	AUXARGS_ENTRY(pos, AT_EGID, imgp->proc->p_ucred->cr_svgid);
	AUXARGS_ENTRY(pos, LINUX_AT_PLATFORM, PTROUT(uplatform));
	AUXARGS_ENTRY(pos, LINUX_AT_RANDOM, imgp->canary);
	if (imgp->execpathp != 0)
		AUXARGS_ENTRY(pos, LINUX_AT_EXECFN, imgp->execpathp);
	if (args->execfd != -1)
		AUXARGS_ENTRY(pos, AT_EXECFD, args->execfd);
	AUXARGS_ENTRY(pos, AT_NULL, 0);

	free(imgp->auxargs, M_TEMP);
	imgp->auxargs = NULL;
	KASSERT(pos - argarray <= LINUX_AT_COUNT, ("Too many auxargs"));

	auxlen = sizeof(*argarray) * (pos - argarray);
	*base -= auxlen;
	copyout(argarray, (void *)*base, auxlen);
	free(argarray, M_TEMP);
}