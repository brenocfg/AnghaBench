#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt; } ;
struct pipe {int pipe_state; scalar_t__ pipe_present; TYPE_2__ pipe_map; TYPE_1__ pipe_buffer; struct pipe* pipe_peer; } ;
struct knote {int /*<<< orphan*/  kn_data; int /*<<< orphan*/  kn_flags; struct pipe* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PIPE_ACTIVE ; 
 int PIPE_EOF ; 
 int /*<<< orphan*/  PIPE_LOCK_ASSERT (struct pipe*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_piperead(struct knote *kn, long hint)
{
	struct pipe *rpipe = kn->kn_hook;
	struct pipe *wpipe = rpipe->pipe_peer;
	int ret;

	PIPE_LOCK_ASSERT(rpipe, MA_OWNED);
	kn->kn_data = rpipe->pipe_buffer.cnt;
	if (kn->kn_data == 0)
		kn->kn_data = rpipe->pipe_map.cnt;

	if ((rpipe->pipe_state & PIPE_EOF) ||
	    wpipe->pipe_present != PIPE_ACTIVE ||
	    (wpipe->pipe_state & PIPE_EOF)) {
		kn->kn_flags |= EV_EOF;
		return (1);
	}
	ret = kn->kn_data > 0;
	return ret;
}