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
struct thread {int /*<<< orphan*/  td_tid; } ;
struct linux_exit_group_args {int /*<<< orphan*/  error_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit1 (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_group ; 

int
linux_exit_group(struct thread *td, struct linux_exit_group_args *args)
{

	LINUX_CTR2(exit_group, "thread(%d) (%d)", td->td_tid,
	    args->error_code);

	/*
	 * XXX: we should send a signal to the parent if
	 * SIGNAL_EXIT_GROUP is set. We ignore that (temporarily?)
	 * as it doesnt occur often.
	 */
	exit1(td, args->error_code, 0);
		/* NOTREACHED */
}