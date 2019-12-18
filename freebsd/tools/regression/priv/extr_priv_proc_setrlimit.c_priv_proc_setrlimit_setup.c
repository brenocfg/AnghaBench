#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct test {int dummy; } ;
struct TYPE_5__ {int rlim_cur; int rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_DATA ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int initialized ; 
 TYPE_1__ rl_base ; 
 TYPE_1__ rl_lowered ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
priv_proc_setrlimit_setup(int asroot, int injail, struct test *test)
{

	if (getrlimit(RLIMIT_DATA, &rl_base) < 0) {
		warn("priv_proc_setrlimit_setup: getrlimit");
		return (-1);
	}

	/*
	 * Must lower current and limit to make sure there's room to try to
	 * raise them during tests.  Set current lower than max so we can
	 * raise it later also.
	 */
	rl_lowered = rl_base;
	rl_lowered.rlim_cur -= 20;
	rl_lowered.rlim_max -= 10;
	if (setrlimit(RLIMIT_DATA, &rl_lowered) < 0) {
		warn("priv_proc_setrlimit_setup: setrlimit");
		return (-1);
	}
	initialized = 1;
	return (0);
}