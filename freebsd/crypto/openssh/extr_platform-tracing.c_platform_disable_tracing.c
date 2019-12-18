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

/* Variables and functions */
 int /*<<< orphan*/  PR_SET_DUMPABLE ; 
 int /*<<< orphan*/  PT_DENY_ATTACH ; 
 int /*<<< orphan*/  __PROC_PROTECT ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setpflags (int /*<<< orphan*/ ,int) ; 

void
platform_disable_tracing(int strict)
{
#if defined(HAVE_PRCTL) && defined(PR_SET_DUMPABLE)
	/* Disable ptrace on Linux without sgid bit */
	if (prctl(PR_SET_DUMPABLE, 0) != 0 && strict)
		fatal("unable to make the process undumpable");
#endif
#if defined(HAVE_SETPFLAGS) && defined(__PROC_PROTECT)
	/* On Solaris, we should make this process untraceable */
	if (setpflags(__PROC_PROTECT, 1) != 0 && strict)
		fatal("unable to make the process untraceable");
#endif
#ifdef PT_DENY_ATTACH
	/* Mac OS X */
	if (ptrace(PT_DENY_ATTACH, 0, 0, 0) == -1 && strict)
		fatal("unable to set PT_DENY_ATTACH");
#endif
}