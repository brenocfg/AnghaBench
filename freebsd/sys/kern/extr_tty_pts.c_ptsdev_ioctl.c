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
struct termios {int dummy; } ;
struct tty {TYPE_2__* t_session; TYPE_1__* t_pgrp; struct termios t_termios; } ;
struct thread {int dummy; } ;
struct pts_softc {int pts_flags; unsigned int pts_unit; } ;
struct fiodgname_arg {int len; } ;
struct file {int /*<<< orphan*/  f_flag; struct tty* f_data; } ;
struct TYPE_4__ {int s_sid; } ;
struct TYPE_3__ {int pg_id; } ;

/* Variables and functions */
 int D_TTY ; 
 int EINVAL ; 
 int ENOIOCTL ; 
 int ENOTTY ; 
#define  FIODGNAME 141 
#define  FIODGNAME_32 140 
#define  FIODTYPE 139 
#define  FIONBIO 138 
#define  FIONREAD 137 
 int NO_PID ; 
 int NSIG ; 
 int PTS_FINISHED ; 
 int PTS_PKT ; 
#define  TIOCGETA 136 
#define  TIOCGPGRP 135 
#define  TIOCGPTN 134 
#define  TIOCGSID 133 
#define  TIOCPKT 132 
#define  TIOCPTMASTER 131 
 int /*<<< orphan*/  TIOCSETA ; 
#define  TIOCSETAF 130 
#define  TIOCSETAW 129 
#define  TIOCSIG 128 
 int copyout (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fiodgname_buf_get_ptr (struct fiodgname_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* tty_devname (struct tty*) ; 
 int tty_ioctl (struct tty*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_signal_pgrp (struct tty*,int) ; 
 struct pts_softc* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttydisc_getc_poll (struct tty*) ; 

__attribute__((used)) static int
ptsdev_ioctl(struct file *fp, u_long cmd, void *data,
    struct ucred *active_cred, struct thread *td)
{
	struct tty *tp = fp->f_data;
	struct pts_softc *psc = tty_softc(tp);
	int error = 0, sig;

	switch (cmd) {
	case FIODTYPE:
		*(int *)data = D_TTY;
		return (0);
	case FIONBIO:
		/* This device supports non-blocking operation. */
		return (0);
	case FIONREAD:
		tty_lock(tp);
		if (psc->pts_flags & PTS_FINISHED) {
			/* Force read() to be called. */
			*(int *)data = 1;
		} else {
			*(int *)data = ttydisc_getc_poll(tp);
		}
		tty_unlock(tp);
		return (0);
	case FIODGNAME:
#ifdef COMPAT_FREEBSD32
	case FIODGNAME_32:
#endif
	{
		struct fiodgname_arg *fgn;
		const char *p;
		int i;

		/* Reverse device name lookups, for ptsname() and ttyname(). */
		fgn = data;
		p = tty_devname(tp);
		i = strlen(p) + 1;
		if (i > fgn->len)
			return (EINVAL);
		return (copyout(p, fiodgname_buf_get_ptr(fgn, cmd), i));
	}

	/*
	 * We need to implement TIOCGPGRP and TIOCGSID here again. When
	 * called on the pseudo-terminal master, it should not check if
	 * the terminal is the foreground terminal of the calling
	 * process.
	 *
	 * TIOCGETA is also implemented here. Various Linux PTY routines
	 * often call isatty(), which is implemented by tcgetattr().
	 */
#ifdef PTS_LINUX
	case TIOCGETA:
		/* Obtain terminal flags through tcgetattr(). */
		tty_lock(tp);
		*(struct termios*)data = tp->t_termios;
		tty_unlock(tp);
		return (0);
#endif /* PTS_LINUX */
	case TIOCSETAF:
	case TIOCSETAW:
		/*
		 * We must make sure we turn tcsetattr() calls of TCSAFLUSH and
		 * TCSADRAIN into something different. If an application would
		 * call TCSAFLUSH or TCSADRAIN on the master descriptor, it may
		 * deadlock waiting for all data to be read.
		 */
		cmd = TIOCSETA;
		break;
#if defined(PTS_COMPAT) || defined(PTS_LINUX)
	case TIOCGPTN:
		/*
		 * Get the device unit number.
		 */
		if (psc->pts_unit < 0)
			return (ENOTTY);
		*(unsigned int *)data = psc->pts_unit;
		return (0);
#endif /* PTS_COMPAT || PTS_LINUX */
	case TIOCGPGRP:
		/* Get the foreground process group ID. */
		tty_lock(tp);
		if (tp->t_pgrp != NULL)
			*(int *)data = tp->t_pgrp->pg_id;
		else
			*(int *)data = NO_PID;
		tty_unlock(tp);
		return (0);
	case TIOCGSID:
		/* Get the session leader process ID. */
		tty_lock(tp);
		if (tp->t_session == NULL)
			error = ENOTTY;
		else
			*(int *)data = tp->t_session->s_sid;
		tty_unlock(tp);
		return (error);
	case TIOCPTMASTER:
		/* Yes, we are a pseudo-terminal master. */
		return (0);
	case TIOCSIG:
		/* Signal the foreground process group. */
		sig = *(int *)data;
		if (sig < 1 || sig >= NSIG)
			return (EINVAL);

		tty_lock(tp);
		tty_signal_pgrp(tp, sig);
		tty_unlock(tp);
		return (0);
	case TIOCPKT:
		/* Enable/disable packet mode. */
		tty_lock(tp);
		if (*(int *)data)
			psc->pts_flags |= PTS_PKT;
		else
			psc->pts_flags &= ~PTS_PKT;
		tty_unlock(tp);
		return (0);
	}

	/* Just redirect this ioctl to the slave device. */
	tty_lock(tp);
	error = tty_ioctl(tp, cmd, data, fp->f_flag, td);
	tty_unlock(tp);
	if (error == ENOIOCTL)
		error = ENOTTY;

	return (error);
}