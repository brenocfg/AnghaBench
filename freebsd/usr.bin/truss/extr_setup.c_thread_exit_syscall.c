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
struct trussinfo {struct threadinfo* curthread; } ;
struct threadinfo {int /*<<< orphan*/  after; int /*<<< orphan*/  in_syscall; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_syscall (struct threadinfo*) ; 
 int /*<<< orphan*/  print_syscall_ret (struct trussinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thread_exit_syscall(struct trussinfo *info)
{
	struct threadinfo *t;

	t = info->curthread;
	if (!t->in_syscall)
		return;

	clock_gettime(CLOCK_REALTIME, &t->after);

	print_syscall_ret(info, 0, NULL);
	free_syscall(t);
}