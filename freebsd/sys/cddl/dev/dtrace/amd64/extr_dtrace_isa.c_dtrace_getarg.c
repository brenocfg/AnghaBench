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
typedef  uintptr_t uint64_t ;
struct trapframe {scalar_t__ tf_rsp; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; } ;
struct amd64_frame {int /*<<< orphan*/  f_retaddr; struct amd64_frame* f_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  CPU_DTRACE_NOFAULT ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 long P2ROUNDUP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dtrace_getfp () ; 
 scalar_t__ dtrace_invop_callsite ; 

uint64_t
dtrace_getarg(int arg, int aframes)
{
	uintptr_t val;
	struct amd64_frame *fp = (struct amd64_frame *)dtrace_getfp();
	uintptr_t *stack;
	int i;

	/*
	 * A total of 6 arguments are passed via registers; any argument with
	 * index of 5 or lower is therefore in a register.
	 */
	int inreg = 5;

	for (i = 1; i <= aframes; i++) {
		fp = fp->f_frame;

		if (P2ROUNDUP(fp->f_retaddr, 16) ==
		    (long)dtrace_invop_callsite) {
			/*
			 * In the case of amd64, we will use the pointer to the
			 * regs structure that was pushed when we took the
			 * trap.  To get this structure, we must increment
			 * beyond the frame structure, and then again beyond
			 * the calling RIP stored in dtrace_invop().  If the
			 * argument that we're seeking is passed on the stack,
			 * we'll pull the true stack pointer out of the saved
			 * registers and decrement our argument by the number
			 * of arguments passed in registers; if the argument
			 * we're seeking is passed in registers, we can just
			 * load it directly.
			 */
			struct trapframe *tf = (struct trapframe *)&fp[1];

			if (arg <= inreg) {
				switch (arg) {
				case 0:
					stack = (uintptr_t *)&tf->tf_rdi;
					break;
				case 1:
					stack = (uintptr_t *)&tf->tf_rsi;
					break;
				case 2:
					stack = (uintptr_t *)&tf->tf_rdx;
					break;
				case 3:
					stack = (uintptr_t *)&tf->tf_rcx;
					break;
				case 4:
					stack = (uintptr_t *)&tf->tf_r8;
					break;
				case 5:
					stack = (uintptr_t *)&tf->tf_r9;
					break;
				}
				arg = 0;
			} else {
				stack = (uintptr_t *)(tf->tf_rsp);
				arg -= inreg;
			}
			goto load;
		}

	}

	/*
	 * We know that we did not come through a trap to get into
	 * dtrace_probe() -- the provider simply called dtrace_probe()
	 * directly.  As this is the case, we need to shift the argument
	 * that we're looking for:  the probe ID is the first argument to
	 * dtrace_probe(), so the argument n will actually be found where
	 * one would expect to find argument (n + 1).
	 */
	arg++;

	if (arg <= inreg) {
		/*
		 * This shouldn't happen.  If the argument is passed in a
		 * register then it should have been, well, passed in a
		 * register...
		 */
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}

	arg -= (inreg + 1);
	stack = (uintptr_t *)&fp[1];

load:
	DTRACE_CPUFLAG_SET(CPU_DTRACE_NOFAULT);
	val = stack[arg];
	DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_NOFAULT);

	return (val);
}