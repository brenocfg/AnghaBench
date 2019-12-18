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
struct cfjail {int flags; scalar_t__* comparam; scalar_t__ pstatus; int /*<<< orphan*/ * comline; } ;

/* Variables and functions */
 scalar_t__ IP_STOP_TIMEOUT ; 
 int JF_FROM_RUNQ ; 
 int JF_SLEEPQ ; 
 int JF_TIMEOUT ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct cfjail* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ WIFSIGNALED (scalar_t__) ; 
 int /*<<< orphan*/  WTERMSIG (scalar_t__) ; 
 int /*<<< orphan*/  failed (struct cfjail*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jail_note (struct cfjail*,char*) ; 
 int /*<<< orphan*/  jail_warnx (struct cfjail*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  paralimit ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  requeue (struct cfjail*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runnable ; 
 scalar_t__ verbose ; 

int
finish_command(struct cfjail *j)
{
	struct cfjail *rj;
	int error;

	if (!(j->flags & JF_SLEEPQ))
		return 0;
	j->flags &= ~JF_SLEEPQ;
	if (*j->comparam == IP_STOP_TIMEOUT) {
		j->flags &= ~JF_TIMEOUT;
		j->pstatus = 0;
		return 0;
	}
	paralimit++;
	if (!TAILQ_EMPTY(&runnable)) {
		rj = TAILQ_FIRST(&runnable);
		rj->flags |= JF_FROM_RUNQ;
		requeue(rj, &ready);
	}
	error = 0;
	if (j->flags & JF_TIMEOUT) {
		j->flags &= ~JF_TIMEOUT;
		if (*j->comparam != IP_STOP_TIMEOUT) {
			jail_warnx(j, "%s: timed out", j->comline);
			failed(j);
			error = -1;
		} else if (verbose > 0)
			jail_note(j, "timed out\n");
	} else if (j->pstatus != 0) {
		if (WIFSIGNALED(j->pstatus))
			jail_warnx(j, "%s: exited on signal %d",
			    j->comline, WTERMSIG(j->pstatus));
		else
			jail_warnx(j, "%s: failed", j->comline);
		j->pstatus = 0;
		failed(j);
		error = -1;
	}
	free(j->comline);
	j->comline = NULL;
	return error;
}