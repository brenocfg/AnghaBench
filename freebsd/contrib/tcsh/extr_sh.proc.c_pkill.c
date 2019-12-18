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
struct process {int p_flags; int /*<<< orphan*/  p_jobid; int /*<<< orphan*/  p_command; int /*<<< orphan*/  p_procid; struct process* p_friends; } ;
typedef  char* pid_t ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int ERR_BADJOB ; 
 int ERR_JOBARGS ; 
 int ERR_NAME ; 
 int ERR_SILENT ; 
 scalar_t__ Isdigit (char) ; 
 int PRUNNING ; 
#define  SIGCONT 132 
 int SIGHUP ; 
#define  SIGSTOP 131 
 int SIGTERM ; 
#define  SIGTSTP 130 
#define  SIGTTIN 129 
#define  SIGTTOU 128 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_push (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char**) ; 
 int /*<<< orphan*/  disabled_cleanup ; 
 int /*<<< orphan*/  errno ; 
 char** glob_all_or_error (char**) ; 
 scalar_t__ kill (char*,int const) ; 
 scalar_t__ killpg (int /*<<< orphan*/ ,int const) ; 
 char* pchild_disabled ; 
 struct process* pfind (char*) ; 
 char* pintr_disabled ; 
 int /*<<< orphan*/  pstart (struct process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote (char*) ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  stderror (int,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strtol (int /*<<< orphan*/ ,char**,int) ; 
 char* strtoul (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,char*,...) ; 

__attribute__((used)) static void
pkill(Char **v, int signum)
{
    struct process *pp, *np;
    int jobflags = 0, err1 = 0;
    pid_t     pid;
    Char *cp, **vp, **globbed;

    /* Avoid globbing %?x patterns */
    for (vp = v; vp && *vp; vp++)
	if (**vp == '%')
	    (void) quote(*vp);

    v = glob_all_or_error(v);
    globbed = v;
    cleanup_push(globbed, blk_cleanup);

    pchild_disabled++;
    cleanup_push(&pchild_disabled, disabled_cleanup);
    if (setintr) {
	pintr_disabled++;
	cleanup_push(&pintr_disabled, disabled_cleanup);
    }

    while (v && (cp = *v)) {
	if (*cp == '%') {
	    np = pp = pfind(cp);
	    do
		jobflags |= np->p_flags;
	    while ((np = np->p_friends) != pp);
#ifdef BSDJOBS
	    switch (signum) {

	    case SIGSTOP:
	    case SIGTSTP:
	    case SIGTTIN:
	    case SIGTTOU:
		if ((jobflags & PRUNNING) == 0) {
# ifdef SUSPENDED
		    xprintf(CGETS(17, 12, "%S: Already suspended\n"), cp);
# else /* !SUSPENDED */
		    xprintf(CGETS(17, 13, "%S: Already stopped\n"), cp);
# endif /* !SUSPENDED */
		    err1++;
		    goto cont;
		}
		break;
		/*
		 * suspend a process, kill -CONT %, then type jobs; the shell
		 * says it is suspended, but it is running; thanks jaap..
		 */
	    case SIGCONT:
		if (!pstart(pp, 0)) {
		    pp->p_procid = 0;
		    stderror(ERR_NAME|ERR_BADJOB, pp->p_command,
			     strerror(errno));
		}
		goto cont;
	    default:
		break;
	    }
#endif /* BSDJOBS */
	    if (killpg(pp->p_jobid, signum) < 0) {
		xprintf("%S: %s\n", cp, strerror(errno));
		err1++;
	    }
#ifdef BSDJOBS
	    if (signum == SIGTERM || signum == SIGHUP)
		(void) killpg(pp->p_jobid, SIGCONT);
#endif /* BSDJOBS */
	}
	else if (!(Isdigit(*cp) || *cp == '-'))
	    stderror(ERR_NAME | ERR_JOBARGS);
	else {
	    char *ep;
#ifndef WINNT_NATIVE
	    pid = strtol(short2str(cp), &ep, 10);
#else
	    pid = strtoul(short2str(cp), &ep, 0);
#endif /* WINNT_NATIVE */
	    if (*ep)
		stderror(ERR_NAME | ERR_JOBARGS);
	    else if (kill(pid, signum) < 0) {
		xprintf("%d: %s\n", pid, strerror(errno));
		err1++;
		goto cont;
	    }
#ifdef BSDJOBS
	    if (signum == SIGTERM || signum == SIGHUP)
		(void) kill(pid, SIGCONT);
#endif /* BSDJOBS */
	}
cont:
	v++;
    }
    cleanup_until(&pchild_disabled);
    if (err1)
	stderror(ERR_SILENT);
}