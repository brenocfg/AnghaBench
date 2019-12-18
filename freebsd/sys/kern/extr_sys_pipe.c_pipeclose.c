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
struct pipepair {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct pipe {scalar_t__ pipe_present; struct pipepair* pipe_pair; TYPE_1__ pipe_sel; int /*<<< orphan*/  pipe_state; struct pipe* pipe_peer; scalar_t__ pipe_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PIPE_ACTIVE ; 
 scalar_t__ PIPE_CLOSING ; 
 int /*<<< orphan*/  PIPE_EOF ; 
 scalar_t__ PIPE_FINALIZED ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_WANT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_pipe_destroy (struct pipepair*) ; 
 int /*<<< orphan*/  msleep (struct pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_free_kmem (struct pipe*) ; 
 int /*<<< orphan*/  pipe_zone ; 
 int /*<<< orphan*/  pipelock (struct pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipeselwakeup (struct pipe*) ; 
 int /*<<< orphan*/  pipeunlock (struct pipe*) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pipepair*) ; 
 int /*<<< orphan*/  wakeup (struct pipe*) ; 

__attribute__((used)) static void
pipeclose(struct pipe *cpipe)
{
	struct pipepair *pp;
	struct pipe *ppipe;

	KASSERT(cpipe != NULL, ("pipeclose: cpipe == NULL"));

	PIPE_LOCK(cpipe);
	pipelock(cpipe, 0);
	pp = cpipe->pipe_pair;

	pipeselwakeup(cpipe);

	/*
	 * If the other side is blocked, wake it up saying that
	 * we want to close it down.
	 */
	cpipe->pipe_state |= PIPE_EOF;
	while (cpipe->pipe_busy) {
		wakeup(cpipe);
		cpipe->pipe_state |= PIPE_WANT;
		pipeunlock(cpipe);
		msleep(cpipe, PIPE_MTX(cpipe), PRIBIO, "pipecl", 0);
		pipelock(cpipe, 0);
	}


	/*
	 * Disconnect from peer, if any.
	 */
	ppipe = cpipe->pipe_peer;
	if (ppipe->pipe_present == PIPE_ACTIVE) {
		pipeselwakeup(ppipe);

		ppipe->pipe_state |= PIPE_EOF;
		wakeup(ppipe);
		KNOTE_LOCKED(&ppipe->pipe_sel.si_note, 0);
	}

	/*
	 * Mark this endpoint as free.  Release kmem resources.  We
	 * don't mark this endpoint as unused until we've finished
	 * doing that, or the pipe might disappear out from under
	 * us.
	 */
	PIPE_UNLOCK(cpipe);
	pipe_free_kmem(cpipe);
	PIPE_LOCK(cpipe);
	cpipe->pipe_present = PIPE_CLOSING;
	pipeunlock(cpipe);

	/*
	 * knlist_clear() may sleep dropping the PIPE_MTX. Set the
	 * PIPE_FINALIZED, that allows other end to free the
	 * pipe_pair, only after the knotes are completely dismantled.
	 */
	knlist_clear(&cpipe->pipe_sel.si_note, 1);
	cpipe->pipe_present = PIPE_FINALIZED;
	seldrain(&cpipe->pipe_sel);
	knlist_destroy(&cpipe->pipe_sel.si_note);

	/*
	 * If both endpoints are now closed, release the memory for the
	 * pipe pair.  If not, unlock.
	 */
	if (ppipe->pipe_present == PIPE_FINALIZED) {
		PIPE_UNLOCK(cpipe);
#ifdef MAC
		mac_pipe_destroy(pp);
#endif
		uma_zfree(pipe_zone, cpipe->pipe_pair);
	} else
		PIPE_UNLOCK(cpipe);
}