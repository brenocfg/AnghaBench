#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  state_func_t ;
struct TYPE_6__ {int se_process; int /*<<< orphan*/  se_started; struct TYPE_6__* se_next; } ;
typedef  TYPE_1__ session_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_session (TYPE_1__*) ; 
 scalar_t__ clean_ttys ; 
 int /*<<< orphan*/  collect_child (int) ; 
 scalar_t__ getsecuritylevel () ; 
 scalar_t__ requested_transition ; 
 scalar_t__ session_has_no_tty (TYPE_1__*) ; 
 TYPE_1__* sessions ; 
 int /*<<< orphan*/  setsecuritylevel (int) ; 
 int start_getty (TYPE_1__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static state_func_t
multi_user(void)
{
	pid_t pid;
	session_t *sp;

	requested_transition = 0;

	/*
	 * If the administrator has not set the security level to -1
	 * to indicate that the kernel should not run multiuser in secure
	 * mode, and the run script has not set a higher level of security
	 * than level 1, then put the kernel into secure mode.
	 */
	if (getsecuritylevel() == 0)
		setsecuritylevel(1);

	for (sp = sessions; sp; sp = sp->se_next) {
		if (sp->se_process)
			continue;
		if (session_has_no_tty(sp))
			continue;
		if ((pid = start_getty(sp)) == -1) {
			/* serious trouble */
			requested_transition = clean_ttys;
			break;
		}
		sp->se_process = pid;
		sp->se_started = time((time_t *) 0);
		add_session(sp);
	}

	while (!requested_transition)
		if ((pid = waitpid(-1, (int *) 0, 0)) != -1)
			collect_child(pid);

	return (state_func_t) requested_transition;
}