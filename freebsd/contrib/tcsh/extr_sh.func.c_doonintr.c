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
struct command {int dummy; } ;
struct TYPE_2__ {scalar_t__ sa_handler; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_TERMINAL ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/ * STRminus ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gointr ; 
 scalar_t__ intty ; 
 TYPE_1__ parintr ; 
 int /*<<< orphan*/  queue_pintr ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sigset_interrupting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/ * strip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
doonintr(Char **v, struct command *c)
{
    Char *cp;
    Char *vv = v[1];

    USE(c);
    if (parintr.sa_handler == SIG_IGN)
	return;
    if (setintr && intty)
	stderror(ERR_NAME | ERR_TERMINAL);
    cp = gointr;
    gointr = 0;
    xfree(cp);
    if (vv == 0) {
	if (setintr)
	    sigset_interrupting(SIGINT, queue_pintr);
	else
	    (void) signal(SIGINT, SIG_DFL);
	gointr = 0;
    }
    else if (eq((vv = strip(vv)), STRminus)) {
	(void) signal(SIGINT, SIG_IGN);
	gointr = Strsave(STRminus);
    }
    else {
	gointr = Strsave(vv);
	sigset_interrupting(SIGINT, queue_pintr);
    }
}