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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct pipe {int /*<<< orphan*/  pipe_state; TYPE_1__ pipe_sel; } ;
struct pipepair {struct pipe pp_wpipe; struct pipe pp_rpipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PIPE_DIRECTOK ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_pipe_create (int /*<<< orphan*/ ,struct pipepair*) ; 
 int /*<<< orphan*/  mac_pipe_init (struct pipepair*) ; 
 int /*<<< orphan*/  pipe_create (struct pipe*,int) ; 
 int /*<<< orphan*/  pipe_zone ; 
 struct pipepair* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pipe_paircreate(struct thread *td, struct pipepair **p_pp)
{
	struct pipepair *pp;
	struct pipe *rpipe, *wpipe;

	*p_pp = pp = uma_zalloc(pipe_zone, M_WAITOK);
#ifdef MAC
	/*
	 * The MAC label is shared between the connected endpoints.  As a
	 * result mac_pipe_init() and mac_pipe_create() are called once
	 * for the pair, and not on the endpoints.
	 */
	mac_pipe_init(pp);
	mac_pipe_create(td->td_ucred, pp);
#endif
	rpipe = &pp->pp_rpipe;
	wpipe = &pp->pp_wpipe;

	knlist_init_mtx(&rpipe->pipe_sel.si_note, PIPE_MTX(rpipe));
	knlist_init_mtx(&wpipe->pipe_sel.si_note, PIPE_MTX(wpipe));

	/* Only the forward direction pipe is backed by default */
	pipe_create(rpipe, 1);
	pipe_create(wpipe, 0);

	rpipe->pipe_state |= PIPE_DIRECTOK;
	wpipe->pipe_state |= PIPE_DIRECTOK;
}