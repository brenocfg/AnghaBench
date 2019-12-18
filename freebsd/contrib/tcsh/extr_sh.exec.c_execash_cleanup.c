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
struct execash_state {int /*<<< orphan*/  OLDSTD; int /*<<< orphan*/  saveSTD; int /*<<< orphan*/  SHDIAG; int /*<<< orphan*/  saveDIAG; int /*<<< orphan*/  SHOUT; int /*<<< orphan*/  saveOUT; int /*<<< orphan*/  SHIN; int /*<<< orphan*/  saveIN; int /*<<< orphan*/  didfds; int /*<<< orphan*/  didcch; int /*<<< orphan*/  sigterm; int /*<<< orphan*/  sigquit; int /*<<< orphan*/  sigint; } ;

/* Variables and functions */
 int /*<<< orphan*/  OLDSTD ; 
 int /*<<< orphan*/  SHDIAG ; 
 int /*<<< orphan*/  SHIN ; 
 int /*<<< orphan*/  SHOUT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  close_on_exec (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  didcch ; 
 int /*<<< orphan*/  didfds ; 
 int /*<<< orphan*/  dmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ doneinp ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xclose (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
execash_cleanup(void *xstate)
{
    struct execash_state *state;

    state = xstate;
    sigaction(SIGINT, &state->sigint, NULL);
    sigaction(SIGQUIT, &state->sigquit, NULL);
    sigaction(SIGTERM, &state->sigterm, NULL);

    doneinp = 0;
#ifndef CLOSE_ON_EXEC
    didcch = state->didcch;
#endif /* CLOSE_ON_EXEC */
    didfds = state->didfds;
    xclose(SHIN);
    xclose(SHOUT);
    xclose(SHDIAG);
    xclose(OLDSTD);
    close_on_exec(SHIN = dmove(state->saveIN, state->SHIN), 1);
    close_on_exec(SHOUT = dmove(state->saveOUT, state->SHOUT), 1);
    close_on_exec(SHDIAG = dmove(state->saveDIAG, state->SHDIAG), 1);
    close_on_exec(OLDSTD = dmove(state->saveSTD, state->OLDSTD), 1);
}