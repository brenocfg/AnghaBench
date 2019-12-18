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
struct process {int p_flags; scalar_t__ p_procid; struct process* p_next; } ;
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {struct process* p_next; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int PRUNNING ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int handle_pending_signals () ; 
 int pintr_disabled ; 
 scalar_t__ pjobs ; 
 TYPE_1__ proclist ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigsuspend (int /*<<< orphan*/ *) ; 

void
dowait(Char **v, struct command *c)
{
    struct process *pp;

    /* the current block mask to be able to restore */
    sigset_t old_mask;

    /* block mask for critical section: OLD_MASK U {SIGCHLD} */
    sigset_t block_mask;

    /* ignore those during blocking sigsuspend:
       OLD_MASK / {SIGCHLD, possibly(SIGINT)} */
    sigset_t pause_mask;

    int opintr_disabled, gotsig;

    USE(c);
    USE(v);
    pjobs++;

    sigprocmask(SIG_BLOCK, NULL, &pause_mask);
    sigdelset(&pause_mask, SIGCHLD);
    if (setintr)
	sigdelset(&pause_mask, SIGINT);

    /* critical section, block also SIGCHLD */
    sigprocmask(SIG_BLOCK, NULL, &block_mask);
    sigaddset(&block_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &block_mask, &old_mask);

    /* detect older SIGCHLDs and remove PRUNNING flag from proclist */
    (void)handle_pending_signals();

loop:
    for (pp = proclist.p_next; pp; pp = pp->p_next)
	if (pp->p_procid &&	/* pp->p_procid == pp->p_jobid && */
	    pp->p_flags & PRUNNING) {
	    /* wait for (or pick up alredy blocked) SIGCHLD */
	    sigsuspend(&pause_mask);

	    /* make the 'wait' interuptable by CTRL-C */
	    opintr_disabled = pintr_disabled;
	    pintr_disabled = 0;
	    gotsig = handle_pending_signals();
	    pintr_disabled = opintr_disabled;
	    if (gotsig)
		break;
	    goto loop;
	}
    pjobs = 0;

    sigprocmask(SIG_SETMASK, &old_mask, NULL);
}