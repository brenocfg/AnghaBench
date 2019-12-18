#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tms_cstime; scalar_t__ tms_cutime; int /*<<< orphan*/  tms_stime; int /*<<< orphan*/  tms_utime; } ;
struct process {scalar_t__ p_procid; scalar_t__ p_jobid; int p_flags; int p_reason; int p_index; struct process* p_friends; TYPE_1__* p_cwd; int /*<<< orphan*/ **** p_btime; int /*<<< orphan*/ **** p_etime; int /*<<< orphan*/  p_stime; int /*<<< orphan*/  p_utime; TYPE_2__ p_rusage; int /*<<< orphan*/  p_command; } ;
struct TYPE_9__ {int /*<<< orphan*/  di_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  pname; } ;
struct TYPE_6__ {int /*<<< orphan*/  di_name; } ;

/* Variables and functions */
 int AMPERSAND ; 
 int AREASON ; 
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int FANCY ; 
 int JOBDIR ; 
 int JOBLIST ; 
 int NAME ; 
 int NUMBER ; 
#define  PAEXITED 133 
 int PALLSTATES ; 
 int PDIAG ; 
 int PDUMPED ; 
#define  PINTERRUPTED 132 
#define  PNEXITED 131 
 int PPOU ; 
 int PPTIME ; 
#define  PRUNNING 130 
#define  PSIGNALED 129 
#define  PSTOPPED 128 
 int PTIME ; 
 int REASON ; 
 int SHELLDIR ; 
 int SIGINT ; 
 int SIGPIPE ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 TYPE_5__* dcwd ; 
 int /*<<< orphan*/  dtildepr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int haderr ; 
 scalar_t__ linbuf ; 
 scalar_t__ linp ; 
 TYPE_2__ lru ; 
 TYPE_3__* mesg ; 
 struct process* pcurrent ; 
 struct process* pprevious ; 
 int /*<<< orphan*/  prusage (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ***,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  ptprint (struct process*) ; 
 int /*<<< orphan*/  sitename (scalar_t__) ; 
 char* xasprintf (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xprintf (char const*,...) ; 
 int /*<<< orphan*/  xputchar (char) ; 
 int /*<<< orphan*/  zru ; 

__attribute__((used)) static int
pprint(struct process *pp, int flag)
{
    int status, reason;
    struct process *tp;
    int     jobflags, pstatus, pcond;
    const char *format;
    int ohaderr;

#ifdef BACKPIPE
    struct process *pipehead = NULL, *pipetail = NULL, *pmarker = NULL;
    int inpipe = 0;
#endif /* BACKPIPE */

    while (pp->p_procid != pp->p_jobid)
	pp = pp->p_friends;
    if (pp == pp->p_friends && (pp->p_flags & PPTIME)) {
	pp->p_flags &= ~PPTIME;
	pp->p_flags |= PTIME;
    }
    tp = pp;
    status = reason = -1;
    jobflags = 0;
    ohaderr = haderr;
    /* Print status to stderr, except for jobs built-in */
    haderr = !(flag & JOBLIST);
    do {
#ifdef BACKPIPE
	/*
	 * The pipeline is reversed, so locate the real head of the pipeline
	 * if pp is at the tail of a pipe (and not already in a pipeline)
	 */
	if ((pp->p_friends->p_flags & PPOU) && !inpipe && (flag & NAME)) {
	    inpipe = 1;
	    pipetail = pp;
	    do 
		pp = pp->p_friends;
	    while (pp->p_friends->p_flags & PPOU);
	    pipehead = pp;
	    pmarker = pp;
	/*
	 * pmarker is used to hold the place of the proc being processed, so
	 * we can search for the next one downstream later.
	 */
	}
	pcond = (tp != pp || (inpipe && tp == pp));
#else /* !BACKPIPE */
	pcond = (tp != pp);
#endif /* BACKPIPE */	    

	jobflags |= pp->p_flags;
	pstatus = (int) (pp->p_flags & PALLSTATES);
	if (pcond && linp != linbuf && !(flag & FANCY) &&
	    ((pstatus == status && pp->p_reason == reason) ||
	     !(flag & REASON)))
	    xputchar(' ');
	else {
	    if (pcond && linp != linbuf)
		xputchar('\n');
	    if (flag & NUMBER) {
#ifdef BACKPIPE
		pcond = ((pp == tp && !inpipe) ||
			 (inpipe && pipetail == tp && pp == pipehead));
#else /* BACKPIPE */
		pcond = (pp == tp);
#endif /* BACKPIPE */
		if (pcond)
		    xprintf("[%d]%s %c ", pp->p_index,
			    pp->p_index < 10 ? " " : "",
			    pp == pcurrent ? '+' :
			    (pp == pprevious ? '-' : ' '));
		else
		    xprintf("       ");
	    }
	    if (flag & FANCY) {
		xprintf("%5d ", pp->p_procid);
#ifdef TCF
		xprintf("%11s ", sitename(pp->p_procid));
#endif /* TCF */
	    }
	    if (flag & (REASON | AREASON)) {
		if (flag & NAME)
		    format = "%-30s";
		else
		    format = "%s";
		if (pstatus == status) {
		    if (pp->p_reason == reason) {
			xprintf(format, "");
			goto prcomd;
		    }
		    else
			reason = (int) pp->p_reason;
		}
		else {
		    status = pstatus;
		    reason = (int) pp->p_reason;
		}
		switch (status) {

		case PRUNNING:
		    xprintf(format, CGETS(17, 4, "Running "));
		    break;

		case PINTERRUPTED:
		case PSTOPPED:
		case PSIGNALED:
		    /*
		     * tell what happened to the background job
		     * From: Michael Schroeder
		     * <mlschroe@immd4.informatik.uni-erlangen.de>
		     */
		    if ((flag & REASON)
			|| ((flag & AREASON)
			    && reason != SIGINT
			    && (reason != SIGPIPE
				|| (pp->p_flags & PPOU) == 0))) {
			char *ptr;
			int free_ptr;

			free_ptr = 0;
			ptr = (char *)(intptr_t)mesg[pp->p_reason & 0177].pname;
			if (ptr == NULL) {
			    ptr = xasprintf("%s %d", CGETS(17, 5, "Signal"),
					    pp->p_reason & 0177);
			    cleanup_push(ptr, xfree);
			    free_ptr = 1;
			}
			xprintf(format, ptr);
			if (free_ptr != 0)
			    cleanup_until(ptr);
		    }
		    else
			reason = -1;
		    break;

		case PNEXITED:
		case PAEXITED:
		    if (flag & REASON) {
			if (pp->p_reason)
			    xprintf(CGETS(17, 6, "Exit %-25d"), pp->p_reason);
			else
			    xprintf(format, CGETS(17, 7, "Done"));
		    }
		    break;

		default:
		    xprintf(CGETS(17, 8, "BUG: status=%-9o"),
			    status);
		}
	    }
	}
prcomd:
	if (flag & NAME) {
	    xprintf("%S", pp->p_command);
	    if (pp->p_flags & PPOU)
		xprintf(" |");
	    if (pp->p_flags & PDIAG)
		xprintf("&");
	}
	if (flag & (REASON | AREASON) && pp->p_flags & PDUMPED)
	    xprintf("%s", CGETS(17, 9, " (core dumped)"));
	if (tp == pp->p_friends) {
	    if (flag & AMPERSAND)
		xprintf(" &");
	    if (flag & JOBDIR &&
		!eq(tp->p_cwd->di_name, dcwd->di_name)) {
		xprintf("%s", CGETS(17, 10, " (wd: "));
		dtildepr(tp->p_cwd->di_name);
		xprintf(")");
	    }
	}
	if (pp->p_flags & PPTIME && !(status & (PSTOPPED | PRUNNING))) {
	    if (linp != linbuf)
		xprintf("\n\t");
#if defined(BSDTIMES) || defined(_SEQUENT_)
	    prusage(&zru, &pp->p_rusage, &pp->p_etime,
		    &pp->p_btime);
#else /* !BSDTIMES && !SEQUENT */
	    lru.tms_utime = pp->p_utime;
	    lru.tms_stime = pp->p_stime;
	    lru.tms_cutime = 0;
	    lru.tms_cstime = 0;
	    prusage(&zru, &lru, pp->p_etime,
		    pp->p_btime);
#endif /* !BSDTIMES && !SEQUENT */

	}
#ifdef BACKPIPE
	pcond = ((tp == pp->p_friends && !inpipe) ||
		 (inpipe && pipehead->p_friends == tp && pp == pipetail));
#else  /* !BACKPIPE */
	pcond = (tp == pp->p_friends);
#endif /* BACKPIPE */
	if (pcond) {
	    if (linp != linbuf)
		xputchar('\n');
	    if (flag & SHELLDIR && !eq(tp->p_cwd->di_name, dcwd->di_name)) {
		xprintf("%s", CGETS(17, 11, "(wd now: "));
		dtildepr(dcwd->di_name);
		xprintf(")\n");
	    }
	}
#ifdef BACKPIPE
	if (inpipe) {
	    /*
	     * if pmaker == pipetail, we are finished that pipeline, and
	     * can now skip to past the head
	     */
	    if (pmarker == pipetail) {
		inpipe = 0;
		pp = pipehead;
	    }
	    else {
	    /*
	     * set pp to one before the one we want next, so the while below
	     * increments to the correct spot.
	     */
		do
		    pp = pp->p_friends;
	    	while (pp->p_friends->p_friends != pmarker);
	    	pmarker = pp->p_friends;
	    }
	}
	pcond = ((pp = pp->p_friends) != tp || inpipe);
#else /* !BACKPIPE */
	pcond = ((pp = pp->p_friends) != tp);
#endif /* BACKPIPE */
    } while (pcond);

    if (jobflags & PTIME && (jobflags & (PSTOPPED | PRUNNING)) == 0) {
	if (jobflags & NUMBER)
	    xprintf("       ");
	ptprint(tp);
    }
    haderr = ohaderr;
    return (jobflags);
}