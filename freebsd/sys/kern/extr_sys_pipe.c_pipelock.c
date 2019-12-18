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
 int /*<<< orphan*/  MA_OWNED ; 
 int PCATCH ; 
 int PIPE_LOCKFL ; 
 int /*<<< orphan*/  PIPE_LOCK_ASSERT (struct pipe*,int /*<<< orphan*/ ) ; 
 int PIPE_LWANT ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int PRIBIO ; 
 int msleep (struct pipe*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
pipelock(struct pipe *cpipe, int catch)
{
	int error;

	PIPE_LOCK_ASSERT(cpipe, MA_OWNED);
	while (cpipe->pipe_state & PIPE_LOCKFL) {
		cpipe->pipe_state |= PIPE_LWANT;
		error = msleep(cpipe, PIPE_MTX(cpipe),
		    catch ? (PRIBIO | PCATCH) : PRIBIO,
		    "pipelk", 0);
		if (error != 0)
			return (error);
	}
	cpipe->pipe_state |= PIPE_LOCKFL;
	return (0);
}