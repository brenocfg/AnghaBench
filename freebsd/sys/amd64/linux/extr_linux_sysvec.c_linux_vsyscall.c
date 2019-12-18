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
typedef  int uint64_t ;
struct trapframe {int tf_rip; int tf_flags; scalar_t__ tf_rsp; int /*<<< orphan*/  tf_rax; } ;
struct thread {struct trapframe* td_frame; } ;
typedef  int /*<<< orphan*/  retqaddr ;

/* Variables and functions */
 int EINVAL ; 
 int LINUX_VSYSCALL_START ; 
 int LINUX_VSYSCALL_SZ ; 
 int PSL_T ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  amd64_syscall (struct thread*,int) ; 
 int copyin (void*,int*,int) ; 
 int /*<<< orphan*/ * linux_vsyscall_vector ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_vsyscall(struct thread *td)
{
	struct trapframe *frame;
	uint64_t retqaddr;
	int code, traced;
	int error;

	frame = td->td_frame;

	/* Check %rip for vsyscall area. */
	if (__predict_true(frame->tf_rip < LINUX_VSYSCALL_START))
		return (EINVAL);
	if ((frame->tf_rip & (LINUX_VSYSCALL_SZ - 1)) != 0)
		return (EINVAL);
	code = (frame->tf_rip - LINUX_VSYSCALL_START) / LINUX_VSYSCALL_SZ;
	if (code >= nitems(linux_vsyscall_vector))
		return (EINVAL);

	/*
	 * vsyscall called as callq *(%rax), so we must
	 * use return address from %rsp and also fixup %rsp.
	 */
	error = copyin((void *)frame->tf_rsp, &retqaddr, sizeof(retqaddr));
	if (error)
		return (error);

	frame->tf_rip = retqaddr;
	frame->tf_rax = linux_vsyscall_vector[code];
	frame->tf_rsp += 8;

	traced = (frame->tf_flags & PSL_T);

	amd64_syscall(td, traced);

	return (0);
}