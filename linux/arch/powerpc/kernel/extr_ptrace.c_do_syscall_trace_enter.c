#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pt_regs {int* gpr; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 long ENOSYS ; 
 int NR_syscalls ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int _TIF_SYSCALL_EMU ; 
 int _TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  audit_syscall_entry (int,int,int,int,int) ; 
 TYPE_1__* current_thread_info () ; 
 scalar_t__ do_seccomp (struct pt_regs*) ; 
 int /*<<< orphan*/  is_32bit_task () ; 
 int test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_enter (struct pt_regs*,int) ; 
 int tracehook_report_syscall_entry (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_exit () ; 

long do_syscall_trace_enter(struct pt_regs *regs)
{
	u32 flags;

	user_exit();

	flags = READ_ONCE(current_thread_info()->flags) &
		(_TIF_SYSCALL_EMU | _TIF_SYSCALL_TRACE);

	if (flags) {
		int rc = tracehook_report_syscall_entry(regs);

		if (unlikely(flags & _TIF_SYSCALL_EMU)) {
			/*
			 * A nonzero return code from
			 * tracehook_report_syscall_entry() tells us to prevent
			 * the syscall execution, but we are not going to
			 * execute it anyway.
			 *
			 * Returning -1 will skip the syscall execution. We want
			 * to avoid clobbering any registers, so we don't goto
			 * the skip label below.
			 */
			return -1;
		}

		if (rc) {
			/*
			 * The tracer decided to abort the syscall. Note that
			 * the tracer may also just change regs->gpr[0] to an
			 * invalid syscall number, that is handled below on the
			 * exit path.
			 */
			goto skip;
		}
	}

	/* Run seccomp after ptrace; allow it to set gpr[3]. */
	if (do_seccomp(regs))
		return -1;

	/* Avoid trace and audit when syscall is invalid. */
	if (regs->gpr[0] >= NR_syscalls)
		goto skip;

	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->gpr[0]);

#ifdef CONFIG_PPC64
	if (!is_32bit_task())
		audit_syscall_entry(regs->gpr[0], regs->gpr[3], regs->gpr[4],
				    regs->gpr[5], regs->gpr[6]);
	else
#endif
		audit_syscall_entry(regs->gpr[0],
				    regs->gpr[3] & 0xffffffff,
				    regs->gpr[4] & 0xffffffff,
				    regs->gpr[5] & 0xffffffff,
				    regs->gpr[6] & 0xffffffff);

	/* Return the possibly modified but valid syscall number */
	return regs->gpr[0];

skip:
	/*
	 * If we are aborting explicitly, or if the syscall number is
	 * now invalid, set the return value to -ENOSYS.
	 */
	regs->gpr[3] = -ENOSYS;
	return -1;
}