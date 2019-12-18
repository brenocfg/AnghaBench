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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uargs ;
struct syscall_args {int code; TYPE_1__* callp; int /*<<< orphan*/  args; } ;
typedef  enum systrace_probe_t { ____Placeholder_systrace_probe_t } systrace_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_4__ {int* t_dtrace_systrace_args; } ;
struct TYPE_3__ {int /*<<< orphan*/  sy_return; int /*<<< orphan*/  (* sy_systrace_args_func ) (int,int /*<<< orphan*/ ,int*,int*) ;int /*<<< orphan*/  sy_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_IDNONE ; 
 int SYSTRACE_ENTRY ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  systrace_args (int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
systrace_probe(struct syscall_args *sa, enum systrace_probe_t type, int retval)
{
	uint64_t uargs[nitems(sa->args)];
	dtrace_id_t id;
	int n_args, sysnum;

	sysnum = sa->code;
	memset(uargs, 0, sizeof(uargs));

	if (type == SYSTRACE_ENTRY) {
		if ((id = sa->callp->sy_entry) == DTRACE_IDNONE)
			return;

		if (sa->callp->sy_systrace_args_func != NULL)
			/*
			 * Convert the syscall parameters using the registered
			 * function.
			 */
			(*sa->callp->sy_systrace_args_func)(sysnum, sa->args,
			    uargs, &n_args);
		else
			/*
			 * Use the built-in system call argument conversion
			 * function to translate the syscall structure fields
			 * into the array of 64-bit values that DTrace expects.
			 */
			systrace_args(sysnum, sa->args, uargs, &n_args);
		/*
		 * Save probe arguments now so that we can retrieve them if
		 * the getargval method is called from further down the stack.
		 */
		curthread->t_dtrace_systrace_args = uargs;
	} else {
		if ((id = sa->callp->sy_return) == DTRACE_IDNONE)
			return;

		curthread->t_dtrace_systrace_args = NULL;
		/* Set arg0 and arg1 as the return value of this syscall. */
		uargs[0] = uargs[1] = retval;
	}

	/* Process the probe using the converted argments. */
	dtrace_probe(id, uargs[0], uargs[1], uargs[2], uargs[3], uargs[4]);
}