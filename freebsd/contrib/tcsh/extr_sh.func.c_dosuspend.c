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
struct sigaction {int dummy; } ;
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_JOBCONTROL ; 
 int /*<<< orphan*/  ERR_SUSPLOG ; 
 int /*<<< orphan*/  ERR_SYSTEM ; 
 int /*<<< orphan*/  FSHTTY ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  errno ; 
 int grabpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ loginsh ; 
 int /*<<< orphan*/  opgrp ; 
 int /*<<< orphan*/  setdisc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shpgrp ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpgrp ; 
 int /*<<< orphan*/  untty () ; 

void
dosuspend(Char **v, struct command *c)
{
#ifdef BSDJOBS
    struct sigaction old;
#endif /* BSDJOBS */

    USE(c);
    USE(v);

    if (loginsh)
	stderror(ERR_SUSPLOG);
    untty();

#ifdef BSDJOBS
    sigaction(SIGTSTP, NULL, &old);
    signal(SIGTSTP, SIG_DFL);
    (void) kill(0, SIGTSTP);
    /* the shell stops here */
    sigaction(SIGTSTP, &old, NULL);
#else /* !BSDJOBS */
    stderror(ERR_JOBCONTROL);
#endif /* BSDJOBS */

#ifdef BSDJOBS
    if (tpgrp != -1) {
	if (grabpgrp(FSHTTY, opgrp) == -1)
	    stderror(ERR_SYSTEM, "tcgetpgrp", strerror(errno));
	(void) setpgid(0, shpgrp);
	(void) tcsetpgrp(FSHTTY, shpgrp);
    }
#endif /* BSDJOBS */
    (void) setdisc(FSHTTY);
}