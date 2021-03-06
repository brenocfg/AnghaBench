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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_DETACH ; 
 int SIGSTOP ; 
 scalar_t__ WIFSTOPPED (int /*<<< orphan*/ ) ; 
 int WSTOPSIG (int /*<<< orphan*/ ) ; 
 scalar_t__ g_pid ; 
 int /*<<< orphan*/  g_status ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
elf_detach(void)
{
	int sig;

	if (g_pid != 0) {
		/*
		 * Forward any pending signals. SIGSTOP is generated by ptrace
		 * itself, so ignore it.
		 */
		sig = WIFSTOPPED(g_status) ? WSTOPSIG(g_status) : 0;
		if (sig == SIGSTOP)
			sig = 0;
		ptrace(PT_DETACH, g_pid, (caddr_t)1, sig);
	}
}