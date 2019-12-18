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
struct execash_state {int SHIN; int SHOUT; int SHDIAG; int OLDSTD; int saveIN; int saveOUT; int saveDIAG; int saveSTD; scalar_t__ didcch; scalar_t__ didfds; int /*<<< orphan*/  sigterm; int /*<<< orphan*/  sigquit; int /*<<< orphan*/  sigint; } ;
struct command {int /*<<< orphan*/  t_dcom; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int OLDSTD ; 
 int SHDIAG ; 
 int SHIN ; 
 int SHOUT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  STRsavehist ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int __nt_really_exec ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ chkstop ; 
 int /*<<< orphan*/  cleanup_push (struct execash_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (struct execash_state*) ; 
 int /*<<< orphan*/  close_on_exec (int,int) ; 
 int dcopy (int,int) ; 
 scalar_t__ didcch ; 
 scalar_t__ didfds ; 
 int /*<<< orphan*/  doexec (struct command*,int) ; 
 int /*<<< orphan*/  execash_cleanup ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  lshift (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mainpid ; 
 int /*<<< orphan*/  panystop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parintr ; 
 int /*<<< orphan*/  parterm ; 
 int /*<<< orphan*/  rechist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ setintr ; 
 int /*<<< orphan*/  shlvl (int) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
execash(Char **t, struct command *kp)
{
    struct execash_state state;

    USE(t);
    if (chkstop == 0 && setintr)
	panystop(0);
    /*
     * Hmm, we don't really want to do that now because we might
     * fail, but what is the choice
     */
    rechist(NULL, adrof(STRsavehist) != NULL);


    sigaction(SIGINT, &parintr, &state.sigint);
    sigaction(SIGQUIT, &parintr, &state.sigquit);
    sigaction(SIGTERM, &parterm, &state.sigterm);

    state.didfds = didfds;
#ifndef CLOSE_ON_EXEC
    state.didcch = didcch;
#endif /* CLOSE_ON_EXEC */
    state.SHIN = SHIN;
    state.SHOUT = SHOUT;
    state.SHDIAG = SHDIAG;
    state.OLDSTD = OLDSTD;

    (void)close_on_exec (state.saveIN = dcopy(SHIN, -1), 1);
    (void)close_on_exec (state.saveOUT = dcopy(SHOUT, -1), 1);
    (void)close_on_exec (state.saveDIAG = dcopy(SHDIAG, -1), 1);
    (void)close_on_exec (state.saveSTD = dcopy(OLDSTD, -1), 1);

    lshift(kp->t_dcom, 1);

    (void)close_on_exec (SHIN = dcopy(0, -1), 1);
    (void)close_on_exec (SHOUT = dcopy(1, -1), 1);
    (void)close_on_exec (SHDIAG = dcopy(2, -1), 1);
#ifndef CLOSE_ON_EXEC
    didcch = 0;
#endif /* CLOSE_ON_EXEC */
    didfds = 0;
    cleanup_push(&state, execash_cleanup);

    /*
     * Decrement the shell level, if not in a subshell
     */
    if (mainpid == getpid())
	shlvl(-1);
#ifdef WINNT_NATIVE
    __nt_really_exec=1;
#endif /* WINNT_NATIVE */
    doexec(kp, 1);

    cleanup_until(&state);
}