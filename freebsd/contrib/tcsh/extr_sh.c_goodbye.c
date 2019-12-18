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
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  STRhome ; 
 int /*<<< orphan*/  STRlogout ; 
 int /*<<< orphan*/  STRnormal ; 
 int /*<<< orphan*/  STRsldtlogout ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  _PATH_DOTLOGOUT ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_pop_mark (size_t) ; 
 size_t cleanup_push_mark () ; 
 int do_logout ; 
 int /*<<< orphan*/  exitstat () ; 
 scalar_t__ loginsh ; 
 int phup_disabled ; 
 int /*<<< orphan*/  record () ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setexit () ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srccat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  varval (int /*<<< orphan*/ ) ; 

void
goodbye(Char **v, struct command *c)
{
    USE(v);
    USE(c);
    record();

    if (loginsh) {
	size_t omark;
	sigset_t set;

	sigemptyset(&set);
	signal(SIGQUIT, SIG_IGN);
	sigaddset(&set, SIGQUIT);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	signal(SIGINT, SIG_IGN);
	sigaddset(&set, SIGINT);
	signal(SIGTERM, SIG_IGN);
	sigaddset(&set, SIGTERM);
	signal(SIGHUP, SIG_IGN);
	sigaddset(&set, SIGHUP);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	phup_disabled = 1;
	setintr = 0;		/* No interrupts after "logout" */
	/* Trap errors inside .logout */
	omark = cleanup_push_mark();
	if (setexit() == 0) {
	    if (!(adrof(STRlogout)))
		setcopy(STRlogout, STRnormal, VAR_READWRITE);
#ifdef _PATH_DOTLOGOUT
	    (void) srcfile(_PATH_DOTLOGOUT, 0, 0, NULL);
#endif
	    if (adrof(STRhome))
		(void) srccat(varval(STRhome), STRsldtlogout);
#ifdef TESLA
	    do_logout = 1;
#endif /* TESLA */
	}
	cleanup_pop_mark(omark);
    }
    exitstat();
}