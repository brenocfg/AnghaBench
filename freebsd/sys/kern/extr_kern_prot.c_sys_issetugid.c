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
struct thread {int* td_retval; struct proc* td_proc; } ;
struct proc {int p_flag; } ;
struct issetugid_args {int dummy; } ;

/* Variables and functions */
 int P_SUGID ; 

int
sys_issetugid(struct thread *td, struct issetugid_args *uap)
{
	struct proc *p = td->td_proc;

	/*
	 * Note: OpenBSD sets a P_SUGIDEXEC flag set at execve() time,
	 * we use P_SUGID because we consider changing the owners as
	 * "tainting" as well.
	 * This is significant for procs that start as root and "become"
	 * a user without an exec - programs cannot know *everything*
	 * that libc *might* have put in their data segment.
	 */
	td->td_retval[0] = (p->p_flag & P_SUGID) ? 1 : 0;
	return (0);
}