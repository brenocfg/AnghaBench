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
struct pipe {int pipe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PIPE_LOCKFL ; 
 int /*<<< orphan*/  PIPE_LOCK_ASSERT (struct pipe*,int /*<<< orphan*/ ) ; 
 int PIPE_LWANT ; 
 int /*<<< orphan*/  wakeup (struct pipe*) ; 

__attribute__((used)) static __inline void
pipeunlock(struct pipe *cpipe)
{

	PIPE_LOCK_ASSERT(cpipe, MA_OWNED);
	KASSERT(cpipe->pipe_state & PIPE_LOCKFL,
		("Unlocked pipe passed to pipeunlock"));
	cpipe->pipe_state &= ~PIPE_LOCKFL;
	if (cpipe->pipe_state & PIPE_LWANT) {
		cpipe->pipe_state &= ~PIPE_LWANT;
		wakeup(cpipe);
	}
}