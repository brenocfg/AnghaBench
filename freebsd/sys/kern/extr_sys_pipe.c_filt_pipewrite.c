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
struct TYPE_2__ {scalar_t__ size; scalar_t__ cnt; } ;
struct pipe {scalar_t__ pipe_present; int pipe_state; TYPE_1__ pipe_buffer; } ;
struct knote {scalar_t__ kn_data; int /*<<< orphan*/  kn_flags; struct pipe* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PIPE_ACTIVE ; 
 scalar_t__ PIPE_BUF ; 
 int PIPE_DIRECTW ; 
 int PIPE_EOF ; 
 int /*<<< orphan*/  PIPE_LOCK_ASSERT (struct pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_pipewrite(struct knote *kn, long hint)
{
	struct pipe *wpipe;

	/*
	 * If this end of the pipe is closed, the knote was removed from the
	 * knlist and the list lock (i.e., the pipe lock) is therefore not held.
	 */
	wpipe = kn->kn_hook;
	if (wpipe->pipe_present != PIPE_ACTIVE ||
	    (wpipe->pipe_state & PIPE_EOF)) {
		kn->kn_data = 0;
		kn->kn_flags |= EV_EOF;
		return (1);
	}
	PIPE_LOCK_ASSERT(wpipe, MA_OWNED);
	kn->kn_data = (wpipe->pipe_buffer.size > 0) ?
	    (wpipe->pipe_buffer.size - wpipe->pipe_buffer.cnt) : PIPE_BUF;
	if (wpipe->pipe_state & PIPE_DIRECTW)
		kn->kn_data = 0;

	return (kn->kn_data >= PIPE_BUF);
}