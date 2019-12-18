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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_4__ {scalar_t__ cnt; scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ cnt; } ;
struct pipe {scalar_t__ pipe_present; int pipe_state; scalar_t__ pipe_wgen; int /*<<< orphan*/  pipe_sel; TYPE_2__ pipe_buffer; TYPE_1__ pipe_map; int /*<<< orphan*/  pipe_pair; } ;
struct file {int f_flag; scalar_t__ f_pipegen; struct pipe* f_data; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 scalar_t__ PIPE_ACTIVE ; 
 scalar_t__ PIPE_BUF ; 
 int PIPE_DIRECTW ; 
 int PIPE_EOF ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int PIPE_NAMED ; 
 struct pipe* PIPE_PEER (struct pipe*) ; 
 int PIPE_SEL ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLINIGNEOF ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int POLLRDBAND ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 scalar_t__ SEL_WAITING (int /*<<< orphan*/ *) ; 
 int mac_pipe_check_poll (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pipe_poll(struct file *fp, int events, struct ucred *active_cred,
    struct thread *td)
{
	struct pipe *rpipe;
	struct pipe *wpipe;
	int levents, revents;
#ifdef MAC
	int error;
#endif

	revents = 0;
	rpipe = fp->f_data;
	wpipe = PIPE_PEER(rpipe);
	PIPE_LOCK(rpipe);
#ifdef MAC
	error = mac_pipe_check_poll(active_cred, rpipe->pipe_pair);
	if (error)
		goto locked_error;
#endif
	if (fp->f_flag & FREAD && events & (POLLIN | POLLRDNORM))
		if (rpipe->pipe_map.cnt > 0 || rpipe->pipe_buffer.cnt > 0)
			revents |= events & (POLLIN | POLLRDNORM);

	if (fp->f_flag & FWRITE && events & (POLLOUT | POLLWRNORM))
		if (wpipe->pipe_present != PIPE_ACTIVE ||
		    (wpipe->pipe_state & PIPE_EOF) ||
		    ((wpipe->pipe_state & PIPE_DIRECTW) == 0 &&
		     ((wpipe->pipe_buffer.size - wpipe->pipe_buffer.cnt) >= PIPE_BUF ||
			 wpipe->pipe_buffer.size == 0)))
			revents |= events & (POLLOUT | POLLWRNORM);

	levents = events &
	    (POLLIN | POLLINIGNEOF | POLLPRI | POLLRDNORM | POLLRDBAND);
	if (rpipe->pipe_state & PIPE_NAMED && fp->f_flag & FREAD && levents &&
	    fp->f_pipegen == rpipe->pipe_wgen)
		events |= POLLINIGNEOF;

	if ((events & POLLINIGNEOF) == 0) {
		if (rpipe->pipe_state & PIPE_EOF) {
			revents |= (events & (POLLIN | POLLRDNORM));
			if (wpipe->pipe_present != PIPE_ACTIVE ||
			    (wpipe->pipe_state & PIPE_EOF))
				revents |= POLLHUP;
		}
	}

	if (revents == 0) {
		if (fp->f_flag & FREAD && events & (POLLIN | POLLRDNORM)) {
			selrecord(td, &rpipe->pipe_sel);
			if (SEL_WAITING(&rpipe->pipe_sel))
				rpipe->pipe_state |= PIPE_SEL;
		}

		if (fp->f_flag & FWRITE && events & (POLLOUT | POLLWRNORM)) {
			selrecord(td, &wpipe->pipe_sel);
			if (SEL_WAITING(&wpipe->pipe_sel))
				wpipe->pipe_state |= PIPE_SEL;
		}
	}
#ifdef MAC
locked_error:
#endif
	PIPE_UNLOCK(rpipe);

	return (revents);
}