#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct process {int p_flags; scalar_t__ p_jobid; struct process* p_friends; struct process* p_next; } ;
struct TYPE_2__ {struct process* p_next; } ;

/* Variables and functions */
 int PFOREGND ; 
 int PHUP ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  STRhangup ; 
 int /*<<< orphan*/  STRhome ; 
 int /*<<< orphan*/  STRlogout ; 
 int /*<<< orphan*/  STRsldtlogout ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  _PATH_DOTLOGOUT ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int killpg (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ loginsh ; 
 TYPE_1__ proclist ; 
 int /*<<< orphan*/  record () ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ shpgrp ; 
 int /*<<< orphan*/  srccat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  varval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int /*<<< orphan*/ ) ; 

void
phup(void)
{
    if (loginsh) {
	setcopy(STRlogout, STRhangup, VAR_READWRITE);
#ifdef _PATH_DOTLOGOUT
	(void) srcfile(_PATH_DOTLOGOUT, 0, 0, NULL);
#endif
	if (adrof(STRhome))
	    (void) srccat(varval(STRhome), STRsldtlogout);
    }

    record();

#ifdef POSIXJOBS 
    /*
     * We kill the last foreground process group. It then becomes
     * responsible to propagate the SIGHUP to its progeny. 
     */
    {
	struct process *pp, *np;

	for (pp = proclist.p_next; pp; pp = pp->p_next) {
	    np = pp;
	    /* 
	     * Find if this job is in the foreground. It could be that
	     * the process leader has exited and the foreground flag
	     * is cleared for it.
	     */
	    do 
		/*
		 * If a process is in the foreground we try to kill
		 * it's process group. If we succeed, then the 
		 * whole job is gone. Otherwise we keep going...
		 * But avoid sending HUP to the shell again.
		 */
		if (((np->p_flags & PFOREGND) != 0) && np->p_jobid != shpgrp) {
		    np->p_flags &= ~PHUP;
		    if (killpg(np->p_jobid, SIGHUP) != -1) {
			/* In case the job was suspended... */
#ifdef SIGCONT
			(void) killpg(np->p_jobid, SIGCONT);
#endif
			break;
		    }
		}
	    while ((np = np->p_friends) != pp);
	}
    }
#endif /* POSIXJOBS */

    xexit(SIGHUP);
}