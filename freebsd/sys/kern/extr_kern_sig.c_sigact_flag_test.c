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
struct sigaction {int sa_flags; scalar_t__ sa_sigaction; } ;
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */
 int SA_SIGINFO ; 
 int /*<<< orphan*/ * SIG_DFL ; 
 int /*<<< orphan*/ * SIG_IGN ; 

__attribute__((used)) static bool
sigact_flag_test(const struct sigaction *act, int flag)
{

	/*
	 * SA_SIGINFO is reset when signal disposition is set to
	 * ignore or default.  Other flags are kept according to user
	 * settings.
	 */
	return ((act->sa_flags & flag) != 0 && (flag != SA_SIGINFO ||
	    ((__sighandler_t *)act->sa_sigaction != SIG_IGN &&
	    (__sighandler_t *)act->sa_sigaction != SIG_DFL)));
}