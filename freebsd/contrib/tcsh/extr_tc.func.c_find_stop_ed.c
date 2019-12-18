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
struct varent {int /*<<< orphan*/ ** vec; } ;
struct process {scalar_t__ p_procid; scalar_t__ p_jobid; int p_flags; int /*<<< orphan*/  p_command; struct process* p_next; } ;
struct TYPE_2__ {struct process* p_next; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int PALLSTATES ; 
 int PINTERRUPTED ; 
 int PSIGNALED ; 
 int PSTOPPED ; 
 int /*<<< orphan*/  STReditors ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ findvv (int /*<<< orphan*/ **,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 struct process* pcurrent ; 
 struct process* pprevious ; 
 TYPE_1__ proclist ; 
 char* short2str (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 
 char* strrchr (char const*,char) ; 

struct process *
find_stop_ed(void)
{
    struct process *pp, *retp;
    const char *ep = NULL, *vp = NULL;
    char *cp, *p;
    size_t epl = 0, vpl = 0;
    int pstatus;
    struct varent *varp;
    Char **vv;

    if (pcurrent == NULL)	/* see if we have any jobs */
	return NULL;		/* nope */

    if ((varp = adrof(STReditors)) != NULL)
	vv = varp->vec;
    else
	vv = NULL;

    if (! vv) {
	if ((ep = getenv("EDITOR")) != NULL) {	/* if we have a value */
	    if ((p = strrchr(ep, '/')) != NULL) 	/* if it has a path */
		ep = p + 1;		/* then we want only the last part */
	}
	else
	    ep = "ed";

	if ((vp = getenv("VISUAL")) != NULL) {	/* if we have a value */
	    if ((p = strrchr(vp, '/')) != NULL) 	/* and it has a path */
		vp = p + 1;		/* then we want only the last part */
	}
	else
	    vp = "vi";

	for (vpl = 0; vp[vpl] && !isspace((unsigned char)vp[vpl]); vpl++)
	    continue;
	for (epl = 0; ep[epl] && !isspace((unsigned char)ep[epl]); epl++)
	    continue;
    }

    retp = NULL;
    for (pp = proclist.p_next; pp; pp = pp->p_next)
	if (pp->p_procid == pp->p_jobid) {

	    /*
	     * Only foreground an edit session if it is suspended.  Some GUI
	     * editors have may be happily running in a separate window, no
	     * point in foregrounding these if they're already running - webb
	     */
	    pstatus = (int) (pp->p_flags & PALLSTATES);
	    if (pstatus != PINTERRUPTED && pstatus != PSTOPPED &&
		pstatus != PSIGNALED)
		continue;

	    p = short2str(pp->p_command);
	    /* get the first word */
	    for (cp = p; *cp && !isspace((unsigned char) *cp); cp++)
		continue;
	    *cp = '\0';
		
	    if ((cp = strrchr(p, '/')) != NULL)	/* and it has a path */
		cp = cp + 1;		/* then we want only the last part */
	    else
		cp = p;			/* else we get all of it */

	    /*
	     * If we find the current name in the $editors array (if set)
	     * or as $EDITOR or $VISUAL (if $editors not set), fg it.
	     */
	    if ((vv && findvv(vv, cp)) ||
	        (epl && strncmp(ep, cp, epl) == 0 && cp[epl] == '\0') ||
		(vpl && strncmp(vp, cp, vpl) == 0 && cp[vpl] == '\0')) {
		/*
		 * If there is a choice, then choose the current process if
		 * available, or the previous process otherwise, or else
		 * anything will do - Robert Webb (robertw@mulga.cs.mu.oz.au).
		 */
		if (pp == pcurrent)
		    return pp;
		else if (retp == NULL || pp == pprevious)
		    retp = pp;
	    }
	}

    return retp;		/* Will be NULL if we didn't find a job */
}