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
struct die_args {int trapnr; int /*<<< orphan*/  regs; int /*<<< orphan*/  err; int /*<<< orphan*/  signr; } ;

/* Variables and functions */
#define  DIE_BREAKPOINT 128 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int kgdb_handle_exception (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __kgdb_notify(struct die_args *args, unsigned long cmd)
{
	int ret;

	switch (cmd) {
	case DIE_BREAKPOINT:
		/*
		 * This means a user thread is single stepping
		 * a system call which should be ignored
		 */
		if (test_thread_flag(TIF_SINGLESTEP))
			return NOTIFY_DONE;

		ret = kgdb_handle_exception(args->trapnr & 0xff, args->signr,
					    args->err, args->regs);
		if (ret)
			return NOTIFY_DONE;

		break;
	}

	return NOTIFY_STOP;
}