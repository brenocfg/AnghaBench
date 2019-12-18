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
typedef  int u_int ;
struct uio {int uio_resid; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ cnt; int out; scalar_t__ in; int /*<<< orphan*/ * buffer; } ;
struct TYPE_3__ {int cnt; int pos; int /*<<< orphan*/  ms; } ;
struct pipe {scalar_t__ pipe_busy; int pipe_state; TYPE_2__ pipe_buffer; int /*<<< orphan*/  pipe_atime; TYPE_1__ pipe_map; int /*<<< orphan*/  pipe_pair; } ;
struct file {int f_flag; struct pipe* f_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FNONBLOCK ; 
 scalar_t__ MINPIPESIZE ; 
 int PCATCH ; 
 scalar_t__ PIPE_BUF ; 
 int PIPE_DIRECTW ; 
 int PIPE_EOF ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int PIPE_WANT ; 
 int PIPE_WANTR ; 
 int PIPE_WANTW ; 
 int PRIBIO ; 
 scalar_t__ SMALL_PIPE_SIZE ; 
 int amountpipekva ; 
 int mac_pipe_check_read (struct ucred*,int /*<<< orphan*/ ) ; 
 int maxpipekva ; 
 int msleep (struct pipe*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int pipelock (struct pipe*,int) ; 
 int piperesizeallowed ; 
 int /*<<< orphan*/  pipeselwakeup (struct pipe*) ; 
 int /*<<< orphan*/  pipespace (struct pipe*,scalar_t__) ; 
 int /*<<< orphan*/  pipeunlock (struct pipe*) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 
 int uiomove_fromphys (int /*<<< orphan*/ ,int,int,struct uio*) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct pipe*) ; 

__attribute__((used)) static int
pipe_read(struct file *fp, struct uio *uio, struct ucred *active_cred,
    int flags, struct thread *td)
{
	struct pipe *rpipe;
	int error;
	int nread = 0;
	int size;

	rpipe = fp->f_data;
	PIPE_LOCK(rpipe);
	++rpipe->pipe_busy;
	error = pipelock(rpipe, 1);
	if (error)
		goto unlocked_error;

#ifdef MAC
	error = mac_pipe_check_read(active_cred, rpipe->pipe_pair);
	if (error)
		goto locked_error;
#endif
	if (amountpipekva > (3 * maxpipekva) / 4) {
		if (!(rpipe->pipe_state & PIPE_DIRECTW) &&
			(rpipe->pipe_buffer.size > SMALL_PIPE_SIZE) &&
			(rpipe->pipe_buffer.cnt <= SMALL_PIPE_SIZE) &&
			(piperesizeallowed == 1)) {
			PIPE_UNLOCK(rpipe);
			pipespace(rpipe, SMALL_PIPE_SIZE);
			PIPE_LOCK(rpipe);
		}
	}

	while (uio->uio_resid) {
		/*
		 * normal pipe buffer receive
		 */
		if (rpipe->pipe_buffer.cnt > 0) {
			size = rpipe->pipe_buffer.size - rpipe->pipe_buffer.out;
			if (size > rpipe->pipe_buffer.cnt)
				size = rpipe->pipe_buffer.cnt;
			if (size > uio->uio_resid)
				size = uio->uio_resid;

			PIPE_UNLOCK(rpipe);
			error = uiomove(
			    &rpipe->pipe_buffer.buffer[rpipe->pipe_buffer.out],
			    size, uio);
			PIPE_LOCK(rpipe);
			if (error)
				break;

			rpipe->pipe_buffer.out += size;
			if (rpipe->pipe_buffer.out >= rpipe->pipe_buffer.size)
				rpipe->pipe_buffer.out = 0;

			rpipe->pipe_buffer.cnt -= size;

			/*
			 * If there is no more to read in the pipe, reset
			 * its pointers to the beginning.  This improves
			 * cache hit stats.
			 */
			if (rpipe->pipe_buffer.cnt == 0) {
				rpipe->pipe_buffer.in = 0;
				rpipe->pipe_buffer.out = 0;
			}
			nread += size;
#ifndef PIPE_NODIRECT
		/*
		 * Direct copy, bypassing a kernel buffer.
		 */
		} else if ((size = rpipe->pipe_map.cnt) != 0) {
			if (size > uio->uio_resid)
				size = (u_int) uio->uio_resid;
			PIPE_UNLOCK(rpipe);
			error = uiomove_fromphys(rpipe->pipe_map.ms,
			    rpipe->pipe_map.pos, size, uio);
			PIPE_LOCK(rpipe);
			if (error)
				break;
			nread += size;
			rpipe->pipe_map.pos += size;
			rpipe->pipe_map.cnt -= size;
			if (rpipe->pipe_map.cnt == 0) {
				rpipe->pipe_state &= ~PIPE_WANTW;
				wakeup(rpipe);
			}
#endif
		} else {
			/*
			 * detect EOF condition
			 * read returns 0 on EOF, no need to set error
			 */
			if (rpipe->pipe_state & PIPE_EOF)
				break;

			/*
			 * If the "write-side" has been blocked, wake it up now.
			 */
			if (rpipe->pipe_state & PIPE_WANTW) {
				rpipe->pipe_state &= ~PIPE_WANTW;
				wakeup(rpipe);
			}

			/*
			 * Break if some data was read.
			 */
			if (nread > 0)
				break;

			/*
			 * Unlock the pipe buffer for our remaining processing.
			 * We will either break out with an error or we will
			 * sleep and relock to loop.
			 */
			pipeunlock(rpipe);

			/*
			 * Handle non-blocking mode operation or
			 * wait for more data.
			 */
			if (fp->f_flag & FNONBLOCK) {
				error = EAGAIN;
			} else {
				rpipe->pipe_state |= PIPE_WANTR;
				if ((error = msleep(rpipe, PIPE_MTX(rpipe),
				    PRIBIO | PCATCH,
				    "piperd", 0)) == 0)
					error = pipelock(rpipe, 1);
			}
			if (error)
				goto unlocked_error;
		}
	}
#ifdef MAC
locked_error:
#endif
	pipeunlock(rpipe);

	/* XXX: should probably do this before getting any locks. */
	if (error == 0)
		vfs_timestamp(&rpipe->pipe_atime);
unlocked_error:
	--rpipe->pipe_busy;

	/*
	 * PIPE_WANT processing only makes sense if pipe_busy is 0.
	 */
	if ((rpipe->pipe_busy == 0) && (rpipe->pipe_state & PIPE_WANT)) {
		rpipe->pipe_state &= ~(PIPE_WANT|PIPE_WANTW);
		wakeup(rpipe);
	} else if (rpipe->pipe_buffer.cnt < MINPIPESIZE) {
		/*
		 * Handle write blocking hysteresis.
		 */
		if (rpipe->pipe_state & PIPE_WANTW) {
			rpipe->pipe_state &= ~PIPE_WANTW;
			wakeup(rpipe);
		}
	}

	if ((rpipe->pipe_buffer.size - rpipe->pipe_buffer.cnt) >= PIPE_BUF)
		pipeselwakeup(rpipe);

	PIPE_UNLOCK(rpipe);
	return (error);
}