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
struct uio {int dummy; } ;
struct TYPE_4__ {scalar_t__ cnt; } ;
struct TYPE_3__ {scalar_t__ cnt; } ;
struct pipe {int pipe_state; TYPE_2__ pipe_map; TYPE_1__ pipe_buffer; } ;

/* Variables and functions */
 int EINTR ; 
 int EPIPE ; 
 int ERESTART ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PCATCH ; 
 int PIPE_DIRECTW ; 
 int PIPE_EOF ; 
 int /*<<< orphan*/  PIPE_LOCK_ASSERT (struct pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int PIPE_WANTR ; 
 int PIPE_WANTW ; 
 int PRIBIO ; 
 int msleep (struct pipe*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int pipe_build_write_buffer (struct pipe*,struct uio*) ; 
 int /*<<< orphan*/  pipe_clone_write_buffer (struct pipe*) ; 
 int /*<<< orphan*/  pipe_destroy_write_buffer (struct pipe*) ; 
 int pipelock (struct pipe*,int) ; 
 int /*<<< orphan*/  pipeselwakeup (struct pipe*) ; 
 int /*<<< orphan*/  pipeunlock (struct pipe*) ; 
 int /*<<< orphan*/  wakeup (struct pipe*) ; 

__attribute__((used)) static int
pipe_direct_write(struct pipe *wpipe, struct uio *uio)
{
	int error;

retry:
	PIPE_LOCK_ASSERT(wpipe, MA_OWNED);
	error = pipelock(wpipe, 1);
	if (error != 0)
		goto error1;
	if ((wpipe->pipe_state & PIPE_EOF) != 0) {
		error = EPIPE;
		pipeunlock(wpipe);
		goto error1;
	}
	if (wpipe->pipe_state & PIPE_DIRECTW) {
		if (wpipe->pipe_state & PIPE_WANTR) {
			wpipe->pipe_state &= ~PIPE_WANTR;
			wakeup(wpipe);
		}
		pipeselwakeup(wpipe);
		wpipe->pipe_state |= PIPE_WANTW;
		pipeunlock(wpipe);
		error = msleep(wpipe, PIPE_MTX(wpipe),
		    PRIBIO | PCATCH, "pipdww", 0);
		if (error)
			goto error1;
		else
			goto retry;
	}
	if (wpipe->pipe_buffer.cnt > 0) {
		if (wpipe->pipe_state & PIPE_WANTR) {
			wpipe->pipe_state &= ~PIPE_WANTR;
			wakeup(wpipe);
		}
		pipeselwakeup(wpipe);
		wpipe->pipe_state |= PIPE_WANTW;
		pipeunlock(wpipe);
		error = msleep(wpipe, PIPE_MTX(wpipe),
		    PRIBIO | PCATCH, "pipdwc", 0);
		if (error)
			goto error1;
		else
			goto retry;
	}

	error = pipe_build_write_buffer(wpipe, uio);
	if (error) {
		pipeunlock(wpipe);
		goto error1;
	}

	while (wpipe->pipe_map.cnt != 0 &&
	    (wpipe->pipe_state & PIPE_EOF) == 0) {
		if (wpipe->pipe_state & PIPE_WANTR) {
			wpipe->pipe_state &= ~PIPE_WANTR;
			wakeup(wpipe);
		}
		pipeselwakeup(wpipe);
		wpipe->pipe_state |= PIPE_WANTW;
		pipeunlock(wpipe);
		error = msleep(wpipe, PIPE_MTX(wpipe), PRIBIO | PCATCH,
		    "pipdwt", 0);
		pipelock(wpipe, 0);
		if (error != 0)
			break;
	}

	if ((wpipe->pipe_state & PIPE_EOF) != 0) {
		wpipe->pipe_map.cnt = 0;
		pipe_destroy_write_buffer(wpipe);
		pipeselwakeup(wpipe);
		error = EPIPE;
	} else if (error == EINTR || error == ERESTART) {
		pipe_clone_write_buffer(wpipe);
	} else {
		pipe_destroy_write_buffer(wpipe);
	}
	pipeunlock(wpipe);
	KASSERT((wpipe->pipe_state & PIPE_DIRECTW) == 0,
	    ("pipe %p leaked PIPE_DIRECTW", wpipe));
	return (error);

error1:
	wakeup(wpipe);
	return (error);
}