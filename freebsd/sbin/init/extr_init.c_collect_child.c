#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_9__ {int se_process; int se_flags; int /*<<< orphan*/  se_started; struct TYPE_9__* se_prev; struct TYPE_9__* se_next; } ;
typedef  TYPE_1__ session_t ;
typedef  int pid_t ;

/* Variables and functions */
 int SE_SHUTDOWN ; 
 int /*<<< orphan*/  add_session (TYPE_1__*) ; 
 int /*<<< orphan*/  clean_ttys ; 
 int /*<<< orphan*/  del_session (TYPE_1__*) ; 
 TYPE_1__* find_session (int) ; 
 int /*<<< orphan*/  free_session (TYPE_1__*) ; 
 int /*<<< orphan*/  requested_transition ; 
 scalar_t__ session_has_no_tty (TYPE_1__*) ; 
 TYPE_1__* sessions ; 
 int start_getty (TYPE_1__*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
collect_child(pid_t pid)
{
	session_t *sp, *sprev, *snext;

	if (! sessions)
		return;

	if (! (sp = find_session(pid)))
		return;

	del_session(sp);
	sp->se_process = 0;

	if (sp->se_flags & SE_SHUTDOWN ||
	    session_has_no_tty(sp)) {
		if ((sprev = sp->se_prev) != NULL)
			sprev->se_next = sp->se_next;
		else
			sessions = sp->se_next;
		if ((snext = sp->se_next) != NULL)
			snext->se_prev = sp->se_prev;
		free_session(sp);
		return;
	}

	if ((pid = start_getty(sp)) == -1) {
		/* serious trouble */
		requested_transition = clean_ttys;
		return;
	}

	sp->se_process = pid;
	sp->se_started = time((time_t *) 0);
	add_session(sp);
}