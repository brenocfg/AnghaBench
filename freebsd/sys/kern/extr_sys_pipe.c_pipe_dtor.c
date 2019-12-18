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
struct pipe {int pipe_state; int /*<<< orphan*/  pipe_sigio; struct pipe* pipe_peer; } ;

/* Variables and functions */
 int PIPE_NAMED ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipeclose (struct pipe*) ; 

void
pipe_dtor(struct pipe *dpipe)
{
	struct pipe *peer;

	peer = (dpipe->pipe_state & PIPE_NAMED) != 0 ? dpipe->pipe_peer : NULL;
	funsetown(&dpipe->pipe_sigio);
	pipeclose(dpipe);
	if (peer != NULL) {
		funsetown(&peer->pipe_sigio);
		pipeclose(peer);
	}
}