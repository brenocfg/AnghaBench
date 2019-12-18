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
struct iovec {int iov_len; void* iov_base; } ;

/* Variables and functions */
 int FP_SIZE ; 
 int /*<<< orphan*/  NT_X86_XSTATE ; 
 int /*<<< orphan*/  PTRACE_GETREGSET ; 
 int /*<<< orphan*/  free (void*) ; 
 int have_xstate_support ; 
 void* malloc (int) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iovec*) ; 

void arch_init_registers(int pid)
{
#ifdef PTRACE_GETREGSET
	void * fp_regs;
	struct iovec iov;

	fp_regs = malloc(FP_SIZE * sizeof(unsigned long));
	if(fp_regs == NULL)
		return;

	iov.iov_base = fp_regs;
	iov.iov_len = FP_SIZE * sizeof(unsigned long);
	if (ptrace(PTRACE_GETREGSET, pid, NT_X86_XSTATE, &iov) == 0)
		have_xstate_support = 1;

	free(fp_regs);
#endif
}