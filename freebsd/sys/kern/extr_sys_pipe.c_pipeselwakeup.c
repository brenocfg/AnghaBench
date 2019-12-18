#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct pipe {int pipe_state; TYPE_1__ pipe_sel; scalar_t__ pipe_sigio; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PIPE_ASYNC ; 
 int /*<<< orphan*/  PIPE_LOCK_ASSERT (struct pipe*,int /*<<< orphan*/ ) ; 
 int PIPE_SEL ; 
 int /*<<< orphan*/  PSOCK ; 
 int /*<<< orphan*/  SEL_WAITING (TYPE_1__*) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  pgsigio (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
pipeselwakeup(struct pipe *cpipe)
{

	PIPE_LOCK_ASSERT(cpipe, MA_OWNED);
	if (cpipe->pipe_state & PIPE_SEL) {
		selwakeuppri(&cpipe->pipe_sel, PSOCK);
		if (!SEL_WAITING(&cpipe->pipe_sel))
			cpipe->pipe_state &= ~PIPE_SEL;
	}
	if ((cpipe->pipe_state & PIPE_ASYNC) && cpipe->pipe_sigio)
		pgsigio(&cpipe->pipe_sigio, SIGIO, 0);
	KNOTE_LOCKED(&cpipe->pipe_sel.si_note, 0);
}