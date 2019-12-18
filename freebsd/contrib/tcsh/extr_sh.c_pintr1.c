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

/* Variables and functions */
 int /*<<< orphan*/  ClearDisp () ; 
 int /*<<< orphan*/  ClearLines () ; 
 int /*<<< orphan*/  Cookedmode () ; 
 int ERR_INTR ; 
 int ERR_NAME ; 
 int ERR_SILENT ; 
 scalar_t__ GettingInput ; 
 scalar_t__ InsideCompletion ; 
 int /*<<< orphan*/  PastBottom () ; 
 int /*<<< orphan*/  dojobs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int doneinp ; 
 int /*<<< orphan*/  drainoline () ; 
 scalar_t__ editing ; 
 int /*<<< orphan*/  endpwent () ; 
 scalar_t__ evalvec ; 
 scalar_t__ gointr ; 
 int /*<<< orphan*/  gotolab (scalar_t__) ; 
 scalar_t__ intty ; 
 int /*<<< orphan*/  jobargv ; 
 scalar_t__ pjobs ; 
 int /*<<< orphan*/  putraw (char) ; 
 int /*<<< orphan*/  reset () ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  xputchar (char) ; 

void
pintr1(int wantnl)
{
    if (setintr) {
	if (pjobs) {
	    pjobs = 0;
	    xputchar('\n');
	    dojobs(jobargv, NULL);
	    stderror(ERR_NAME | ERR_INTR);
	}
    }
    /* MH - handle interrupted completions specially */
    {
	if (InsideCompletion)
	    stderror(ERR_SILENT);
    }
    /* JV - Make sure we shut off inputl */
    {
	(void) Cookedmode();
	GettingInput = 0;
	if (evalvec)
	    doneinp = 1;
    }
    drainoline();
#ifdef HAVE_GETPWENT
    (void) endpwent();
#endif

    /*
     * If we have an active "onintr" then we search for the label. Note that if
     * one does "onintr -" then we shan't be interruptible so we needn't worry
     * about that here.
     */
    if (gointr) {
	gotolab(gointr);
	reset();
    }
    else if (intty && wantnl) {
	if (editing) {
	    /* 
	     * If we are editing a multi-line input command, and move to
	     * the beginning of the line, we don't want to trash it when
	     * we hit ^C
	     */
	    PastBottom();
	    ClearLines();
	    ClearDisp();
	}
	else {
	    /* xputchar('\n'); *//* Some like this, others don't */
	    (void) putraw('\r');
	    (void) putraw('\n');
	}
    }
    stderror(ERR_SILENT);
}