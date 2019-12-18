#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int32_t ;
struct image_params {char* execpath; uintptr_t execpathp; uintptr_t canary; int canarylen; uintptr_t pagesizes; int pagesizeslen; TYPE_5__* args; TYPE_4__* sysent; int /*<<< orphan*/ * auxargs; TYPE_3__* proc; } ;
struct freebsd32_ps_strings {int ps_argvstr; int ps_nargvstr; int ps_envstr; int ps_nenvstr; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  pagesizes32 ;
typedef  char int32_t ;
typedef  int /*<<< orphan*/  canary ;
struct TYPE_12__ {TYPE_1__* p_sysent; } ;
struct TYPE_11__ {uintptr_t stringspace; int argc; int envc; char* begin_argv; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* sv_copyout_auxargs ) (struct image_params*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* sv_stackgap ) (struct image_params*,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_2__* p_sysent; } ;
struct TYPE_8__ {scalar_t__ sv_sigcode_base; int* sv_szsigcode; char* sv_sigcode; } ;
struct TYPE_7__ {scalar_t__ sv_psstrings; } ;

/* Variables and functions */
 uintptr_t ARG_MAX ; 
 int MAXPAGESIZES ; 
 int /*<<< orphan*/  arc4rand (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyout (char*,void*,uintptr_t) ; 
 TYPE_6__* curproc ; 
 int /*<<< orphan*/ * pagesizes ; 
 uintptr_t rounddown2 (uintptr_t,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (struct image_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct image_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suword32 (int*,int) ; 

register_t *
freebsd32_copyout_strings(struct image_params *imgp)
{
	int argc, envc, i;
	u_int32_t *vectp;
	char *stringp;
	uintptr_t destp;
	u_int32_t *stack_base;
	struct freebsd32_ps_strings *arginfo;
	char canary[sizeof(long) * 8];
	int32_t pagesizes32[MAXPAGESIZES];
	size_t execpath_len;
	int szsigcode;

	/*
	 * Calculate string base and vector table pointers.
	 * Also deal with signal trampoline code for this exec type.
	 */
	if (imgp->execpath != NULL && imgp->auxargs != NULL)
		execpath_len = strlen(imgp->execpath) + 1;
	else
		execpath_len = 0;
	arginfo = (struct freebsd32_ps_strings *)curproc->p_sysent->
	    sv_psstrings;
	if (imgp->proc->p_sysent->sv_sigcode_base == 0)
		szsigcode = *(imgp->proc->p_sysent->sv_szsigcode);
	else
		szsigcode = 0;
	destp =	(uintptr_t)arginfo;

	/*
	 * install sigcode
	 */
	if (szsigcode != 0) {
		destp -= szsigcode;
		destp = rounddown2(destp, sizeof(uint32_t));
		copyout(imgp->proc->p_sysent->sv_sigcode, (void *)destp,
		    szsigcode);
	}

	/*
	 * Copy the image path for the rtld.
	 */
	if (execpath_len != 0) {
		destp -= execpath_len;
		imgp->execpathp = destp;
		copyout(imgp->execpath, (void *)destp, execpath_len);
	}

	/*
	 * Prepare the canary for SSP.
	 */
	arc4rand(canary, sizeof(canary), 0);
	destp -= sizeof(canary);
	imgp->canary = destp;
	copyout(canary, (void *)destp, sizeof(canary));
	imgp->canarylen = sizeof(canary);

	/*
	 * Prepare the pagesizes array.
	 */
	for (i = 0; i < MAXPAGESIZES; i++)
		pagesizes32[i] = (uint32_t)pagesizes[i];
	destp -= sizeof(pagesizes32);
	destp = rounddown2(destp, sizeof(uint32_t));
	imgp->pagesizes = destp;
	copyout(pagesizes32, (void *)destp, sizeof(pagesizes32));
	imgp->pagesizeslen = sizeof(pagesizes32);

	destp -= ARG_MAX - imgp->args->stringspace;
	destp = rounddown2(destp, sizeof(uint32_t));

	vectp = (uint32_t *)destp;
	if (imgp->sysent->sv_stackgap != NULL)
		imgp->sysent->sv_stackgap(imgp, (u_long *)&vectp);

	if (imgp->auxargs)
		imgp->sysent->sv_copyout_auxargs(imgp, (u_long *)&vectp);

	/*
	 * Allocate room for the argv[] and env vectors including the
	 * terminating NULL pointers.
	 */
	vectp -= imgp->args->argc + 1 + imgp->args->envc + 1;

	/*
	 * vectp also becomes our initial stack base
	 */
	stack_base = vectp;

	stringp = imgp->args->begin_argv;
	argc = imgp->args->argc;
	envc = imgp->args->envc;
	/*
	 * Copy out strings - arguments and environment.
	 */
	copyout(stringp, (void *)destp, ARG_MAX - imgp->args->stringspace);

	/*
	 * Fill in "ps_strings" struct for ps, w, etc.
	 */
	suword32(&arginfo->ps_argvstr, (u_int32_t)(intptr_t)vectp);
	suword32(&arginfo->ps_nargvstr, argc);

	/*
	 * Fill in argument portion of vector table.
	 */
	for (; argc > 0; --argc) {
		suword32(vectp++, (u_int32_t)(intptr_t)destp);
		while (*stringp++ != 0)
			destp++;
		destp++;
	}

	/* a null vector table pointer separates the argp's from the envp's */
	suword32(vectp++, 0);

	suword32(&arginfo->ps_envstr, (u_int32_t)(intptr_t)vectp);
	suword32(&arginfo->ps_nenvstr, envc);

	/*
	 * Fill in environment portion of vector table.
	 */
	for (; envc > 0; --envc) {
		suword32(vectp++, (u_int32_t)(intptr_t)destp);
		while (*stringp++ != 0)
			destp++;
		destp++;
	}

	/* end of vector table is a null pointer */
	suword32(vectp, 0);

	return ((register_t *)stack_base);
}