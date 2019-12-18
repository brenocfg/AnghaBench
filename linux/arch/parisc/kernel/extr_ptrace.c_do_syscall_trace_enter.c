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
typedef  scalar_t__ u32 ;
struct pt_regs {unsigned long* gr; } ;

/* Variables and functions */
 unsigned long ENOSYS ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int /*<<< orphan*/  audit_syscall_entry (int,int,int,int,int) ; 
 int /*<<< orphan*/  is_compat_task () ; 
 int secure_computing (int /*<<< orphan*/ *) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_enter (struct pt_regs*,unsigned long) ; 
 int tracehook_report_syscall_entry (struct pt_regs*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

long do_syscall_trace_enter(struct pt_regs *regs)
{
	if (test_thread_flag(TIF_SYSCALL_TRACE)) {
		int rc = tracehook_report_syscall_entry(regs);

		/*
		 * As tracesys_next does not set %r28 to -ENOSYS
		 * when %r20 is set to -1, initialize it here.
		 */
		regs->gr[28] = -ENOSYS;

		if (rc) {
			/*
			 * A nonzero return code from
			 * tracehook_report_syscall_entry() tells us
			 * to prevent the syscall execution.  Skip
			 * the syscall call and the syscall restart handling.
			 *
			 * Note that the tracer may also just change
			 * regs->gr[20] to an invalid syscall number,
			 * that is handled by tracesys_next.
			 */
			regs->gr[20] = -1UL;
			return -1;
		}
	}

	/* Do the secure computing check after ptrace. */
	if (secure_computing(NULL) == -1)
		return -1;

#ifdef CONFIG_HAVE_SYSCALL_TRACEPOINTS
	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->gr[20]);
#endif

#ifdef CONFIG_64BIT
	if (!is_compat_task())
		audit_syscall_entry(regs->gr[20], regs->gr[26], regs->gr[25],
				    regs->gr[24], regs->gr[23]);
	else
#endif
		audit_syscall_entry(regs->gr[20] & 0xffffffff,
			regs->gr[26] & 0xffffffff,
			regs->gr[25] & 0xffffffff,
			regs->gr[24] & 0xffffffff,
			regs->gr[23] & 0xffffffff);

	/*
	 * Sign extend the syscall number to 64bit since it may have been
	 * modified by a compat ptrace call
	 */
	return (int) ((u32) regs->gr[20]);
}