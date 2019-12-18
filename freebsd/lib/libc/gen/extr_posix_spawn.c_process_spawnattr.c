#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_flags; } ;
typedef  TYPE_1__* posix_spawnattr_t ;
struct TYPE_3__ {int sa_flags; int /*<<< orphan*/  sa_sigdefault; int /*<<< orphan*/  sa_sigmask; int /*<<< orphan*/  sa_schedparam; int /*<<< orphan*/  sa_schedpolicy; int /*<<< orphan*/  sa_pgroup; } ;

/* Variables and functions */
 int POSIX_SPAWN_RESETIDS ; 
 int POSIX_SPAWN_SETPGROUP ; 
 int POSIX_SPAWN_SETSCHEDPARAM ; 
 int POSIX_SPAWN_SETSCHEDULER ; 
 int POSIX_SPAWN_SETSIGDEF ; 
 int POSIX_SPAWN_SETSIGMASK ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int _SIG_MAXSIG ; 
 scalar_t__ __sys_sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sys_sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ sched_setparam (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setegid (int /*<<< orphan*/ ) ; 
 scalar_t__ seteuid (int /*<<< orphan*/ ) ; 
 scalar_t__ setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
process_spawnattr(const posix_spawnattr_t sa)
{
	struct sigaction sigact = { .sa_flags = 0, .sa_handler = SIG_DFL };
	int i;

	/*
	 * POSIX doesn't really describe in which order everything
	 * should be set. We'll just set them in the order in which they
	 * are mentioned.
	 */

	/* Set process group */
	if (sa->sa_flags & POSIX_SPAWN_SETPGROUP) {
		if (setpgid(0, sa->sa_pgroup) != 0)
			return (errno);
	}

	/* Set scheduler policy */
	if (sa->sa_flags & POSIX_SPAWN_SETSCHEDULER) {
		if (sched_setscheduler(0, sa->sa_schedpolicy,
		    &sa->sa_schedparam) != 0)
			return (errno);
	} else if (sa->sa_flags & POSIX_SPAWN_SETSCHEDPARAM) {
		if (sched_setparam(0, &sa->sa_schedparam) != 0)
			return (errno);
	}

	/* Reset user ID's */
	if (sa->sa_flags & POSIX_SPAWN_RESETIDS) {
		if (setegid(getgid()) != 0)
			return (errno);
		if (seteuid(getuid()) != 0)
			return (errno);
	}

	/*
	 * Set signal masks/defaults.
	 * Use unwrapped syscall, libthr is in undefined state after vfork().
	 */
	if (sa->sa_flags & POSIX_SPAWN_SETSIGMASK) {
		__sys_sigprocmask(SIG_SETMASK, &sa->sa_sigmask, NULL);
	}

	if (sa->sa_flags & POSIX_SPAWN_SETSIGDEF) {
		for (i = 1; i <= _SIG_MAXSIG; i++) {
			if (sigismember(&sa->sa_sigdefault, i))
				if (__sys_sigaction(i, &sigact, NULL) != 0)
					return (errno);
		}
	}

	return (0);
}