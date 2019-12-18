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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int /*<<< orphan*/  do_signal (struct pt_regs*) ; 
 scalar_t__ test_and_clear_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_notify_resume (struct pt_regs*) ; 

void do_notify_resume(struct pt_regs *regs)
{
	if (test_thread_flag(TIF_SIGPENDING))
		do_signal(regs);

	if (test_and_clear_thread_flag(TIF_NOTIFY_RESUME))
		tracehook_notify_resume(regs);
}