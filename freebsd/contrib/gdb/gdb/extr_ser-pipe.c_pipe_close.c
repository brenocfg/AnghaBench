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
struct serial {int fd; struct pipe_state* state; } ;
struct pipe_state {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct pipe_state*) ; 

__attribute__((used)) static void
pipe_close (struct serial *scb)
{
  struct pipe_state *state = scb->state;
  if (state != NULL)
    {
      int pid = state->pid;
      close (scb->fd);
      scb->fd = -1;
      xfree (state);
      scb->state = NULL;
      kill (pid, SIGTERM);
      /* Might be useful to check that the child does die. */
    }
}