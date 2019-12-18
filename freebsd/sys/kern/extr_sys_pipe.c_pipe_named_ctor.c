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
struct thread {int dummy; } ;
struct pipe {int /*<<< orphan*/  pipe_state; } ;
struct pipepair {struct pipe pp_rpipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_NAMED ; 
 int /*<<< orphan*/  pipe_paircreate (struct thread*,struct pipepair**) ; 

void
pipe_named_ctor(struct pipe **ppipe, struct thread *td)
{
	struct pipepair *pp;

	pipe_paircreate(td, &pp);
	pp->pp_rpipe.pipe_state |= PIPE_NAMED;
	*ppipe = &pp->pp_rpipe;
}