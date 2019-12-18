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
typedef  int /*<<< orphan*/  u_long ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_4__ {int cnt; } ;
struct TYPE_3__ {int cnt; } ;
struct pipe {int /*<<< orphan*/  pipe_sigio; TYPE_2__ pipe_buffer; TYPE_1__ pipe_map; int /*<<< orphan*/  pipe_state; int /*<<< orphan*/  pipe_pair; } ;
struct file {int f_flag; struct pipe* f_data; } ;

/* Variables and functions */
 int ENOTTY ; 
#define  FIOASYNC 134 
#define  FIOGETOWN 133 
#define  FIONBIO 132 
#define  FIONREAD 131 
#define  FIOSETOWN 130 
 int FREAD ; 
 int /*<<< orphan*/  PIPE_ASYNC ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
#define  TIOCGPGRP 129 
#define  TIOCSPGRP 128 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int mac_pipe_check_ioctl (struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
pipe_ioctl(struct file *fp, u_long cmd, void *data, struct ucred *active_cred,
    struct thread *td)
{
	struct pipe *mpipe = fp->f_data;
	int error;

	PIPE_LOCK(mpipe);

#ifdef MAC
	error = mac_pipe_check_ioctl(active_cred, mpipe->pipe_pair, cmd, data);
	if (error) {
		PIPE_UNLOCK(mpipe);
		return (error);
	}
#endif

	error = 0;
	switch (cmd) {

	case FIONBIO:
		break;

	case FIOASYNC:
		if (*(int *)data) {
			mpipe->pipe_state |= PIPE_ASYNC;
		} else {
			mpipe->pipe_state &= ~PIPE_ASYNC;
		}
		break;

	case FIONREAD:
		if (!(fp->f_flag & FREAD)) {
			*(int *)data = 0;
			PIPE_UNLOCK(mpipe);
			return (0);
		}
		if (mpipe->pipe_map.cnt != 0)
			*(int *)data = mpipe->pipe_map.cnt;
		else
			*(int *)data = mpipe->pipe_buffer.cnt;
		break;

	case FIOSETOWN:
		PIPE_UNLOCK(mpipe);
		error = fsetown(*(int *)data, &mpipe->pipe_sigio);
		goto out_unlocked;

	case FIOGETOWN:
		*(int *)data = fgetown(&mpipe->pipe_sigio);
		break;

	/* This is deprecated, FIOSETOWN should be used instead. */
	case TIOCSPGRP:
		PIPE_UNLOCK(mpipe);
		error = fsetown(-(*(int *)data), &mpipe->pipe_sigio);
		goto out_unlocked;

	/* This is deprecated, FIOGETOWN should be used instead. */
	case TIOCGPGRP:
		*(int *)data = -fgetown(&mpipe->pipe_sigio);
		break;

	default:
		error = ENOTTY;
		break;
	}
	PIPE_UNLOCK(mpipe);
out_unlocked:
	return (error);
}