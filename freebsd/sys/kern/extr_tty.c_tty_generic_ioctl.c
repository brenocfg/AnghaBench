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
typedef  int u_long ;
struct winsize {int dummy; } ;
struct termios {int c_iflag; int c_lflag; int c_cflag; int /*<<< orphan*/ * c_cc; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;
struct tty {int t_drainwait; int /*<<< orphan*/  t_flags; struct winsize t_winsize; int /*<<< orphan*/  t_bgwait; struct pgrp* t_pgrp; int /*<<< orphan*/  t_sessioncnt; TYPE_2__* t_session; struct termios t_termios; int /*<<< orphan*/  t_inq; int /*<<< orphan*/  t_sigio; int /*<<< orphan*/  t_outq; } ;
struct thread {struct proc* td_proc; } ;
struct proc {TYPE_2__* p_session; int /*<<< orphan*/  p_flag; struct pgrp* p_pgrp; } ;
struct pgrp {int pg_id; TYPE_2__* pg_session; } ;
struct TYPE_4__ {int s_sid; struct tty* s_ttyp; TYPE_1__* s_ttyvp; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_type; } ;

/* Variables and functions */
 int CIGNORE ; 
 int /*<<< orphan*/  CTRL (char) ; 
 int EACCES ; 
 int EBUSY ; 
 int ENOIOCTL ; 
 int ENOTTY ; 
 int EPERM ; 
#define  FIOASYNC 162 
#define  FIOGETOWN 161 
#define  FIONBIO 160 
#define  FIONREAD 159 
#define  FIONWRITE 158 
#define  FIOSETOWN 157 
 int FREAD ; 
 int FWRITE ; 
 int ICANON ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  MPASS (TYPE_2__*) ; 
 int NO_PID ; 
 int /*<<< orphan*/  PGRP_UNLOCK (struct pgrp*) ; 
 int /*<<< orphan*/  PRIV_TTY_CONSOLE ; 
 int /*<<< orphan*/  PRIV_TTY_DRAINWAIT ; 
 int /*<<< orphan*/  PRIV_TTY_STI ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  P_CONTROLT ; 
 int SER_DTR ; 
 int /*<<< orphan*/  SESS_LEADER (struct proc*) ; 
 int /*<<< orphan*/  TF_ASYNC ; 
 int /*<<< orphan*/  TF_EXCLUDE ; 
 int /*<<< orphan*/  TF_STOPPED ; 
#define  TIOCCDTR 156 
#define  TIOCCONS 155 
#define  TIOCDRAIN 154 
#define  TIOCEXCL 153 
#define  TIOCFLUSH 152 
#define  TIOCGDRAINWAIT 151 
#define  TIOCGETA 150 
#define  TIOCGETD 149 
#define  TIOCGPGRP 148 
#define  TIOCGSID 147 
#define  TIOCGWINSZ 146 
#define  TIOCMBIC 145 
#define  TIOCMBIS 144 
#define  TIOCMGET 143 
#define  TIOCMSET 142 
 int TIOCM_DTR ; 
 int /*<<< orphan*/  TIOCM_LE ; 
 int TIOCM_RTS ; 
#define  TIOCNXCL 141 
#define  TIOCOUTQ 140 
 int /*<<< orphan*/  TIOCPKT_DOSTOP ; 
 int /*<<< orphan*/  TIOCPKT_NOSTOP ; 
 int /*<<< orphan*/  TIOCPKT_START ; 
 int /*<<< orphan*/  TIOCPKT_STOP ; 
#define  TIOCSCTTY 139 
#define  TIOCSDRAINWAIT 138 
#define  TIOCSDTR 137 
#define  TIOCSETA 136 
#define  TIOCSETAF 135 
#define  TIOCSETAW 134 
#define  TIOCSPGRP 133 
#define  TIOCSTART 132 
#define  TIOCSTAT 131 
#define  TIOCSTI 130 
#define  TIOCSTOP 129 
#define  TIOCSWINSZ 128 
 int TTYDISC ; 
 int TTYSUP_CFLAG ; 
 int TTYSUP_IFLAG ; 
 int TTYSUP_LFLAG ; 
 int /*<<< orphan*/  TTYSUP_OFLAG ; 
 int /*<<< orphan*/  VBAD ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 struct tty* constty ; 
 int /*<<< orphan*/  constty_clear () ; 
 int /*<<< orphan*/  constty_set (struct tty*) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int fgetown (int /*<<< orphan*/ *) ; 
 int fsetown (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 struct pgrp* pgfind (int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int tty_drain (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flush (struct tty*,int) ; 
 int /*<<< orphan*/  tty_info (struct tty*) ; 
 int tty_ioctl_compat (struct tty*,int,void*,int,struct thread*) ; 
 int /*<<< orphan*/  tty_is_ctty (struct tty*,struct proc*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_set_winsize (struct tty*,void*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty*,int) ; 
 int tty_watermarks (struct tty*) ; 
 int ttydevsw_modem (struct tty*,int,int) ; 
 int /*<<< orphan*/  ttydevsw_outwakeup (struct tty*) ; 
 int ttydevsw_param (struct tty*,struct termios*) ; 
 int /*<<< orphan*/  ttydevsw_pktnotify (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_optimize (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int ttyinq_bytescanonicalized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyinq_canonicalize (int /*<<< orphan*/ *) ; 
 int ttyoutq_bytesused (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tty_generic_ioctl(struct tty *tp, u_long cmd, void *data, int fflag,
    struct thread *td)
{
	int error;

	switch (cmd) {
	/*
	 * Modem commands.
	 * The SER_* and TIOCM_* flags are the same, but one bit
	 * shifted. I don't know why.
	 */
	case TIOCSDTR:
		ttydevsw_modem(tp, SER_DTR, 0);
		return (0);
	case TIOCCDTR:
		ttydevsw_modem(tp, 0, SER_DTR);
		return (0);
	case TIOCMSET: {
		int bits = *(int *)data;
		ttydevsw_modem(tp,
		    (bits & (TIOCM_DTR | TIOCM_RTS)) >> 1,
		    ((~bits) & (TIOCM_DTR | TIOCM_RTS)) >> 1);
		return (0);
	}
	case TIOCMBIS: {
		int bits = *(int *)data;
		ttydevsw_modem(tp, (bits & (TIOCM_DTR | TIOCM_RTS)) >> 1, 0);
		return (0);
	}
	case TIOCMBIC: {
		int bits = *(int *)data;
		ttydevsw_modem(tp, 0, (bits & (TIOCM_DTR | TIOCM_RTS)) >> 1);
		return (0);
	}
	case TIOCMGET:
		*(int *)data = TIOCM_LE + (ttydevsw_modem(tp, 0, 0) << 1);
		return (0);

	case FIOASYNC:
		if (*(int *)data)
			tp->t_flags |= TF_ASYNC;
		else
			tp->t_flags &= ~TF_ASYNC;
		return (0);
	case FIONBIO:
		/* This device supports non-blocking operation. */
		return (0);
	case FIONREAD:
		*(int *)data = ttyinq_bytescanonicalized(&tp->t_inq);
		return (0);
	case FIONWRITE:
	case TIOCOUTQ:
		*(int *)data = ttyoutq_bytesused(&tp->t_outq);
		return (0);
	case FIOSETOWN:
		if (tp->t_session != NULL && !tty_is_ctty(tp, td->td_proc))
			/* Not allowed to set ownership. */
			return (ENOTTY);

		/* Temporarily unlock the TTY to set ownership. */
		tty_unlock(tp);
		error = fsetown(*(int *)data, &tp->t_sigio);
		tty_lock(tp);
		return (error);
	case FIOGETOWN:
		if (tp->t_session != NULL && !tty_is_ctty(tp, td->td_proc))
			/* Not allowed to set ownership. */
			return (ENOTTY);

		/* Get ownership. */
		*(int *)data = fgetown(&tp->t_sigio);
		return (0);
	case TIOCGETA:
		/* Obtain terminal flags through tcgetattr(). */
		*(struct termios*)data = tp->t_termios;
		return (0);
	case TIOCSETA:
	case TIOCSETAW:
	case TIOCSETAF: {
		struct termios *t = data;

		/*
		 * Who makes up these funny rules? According to POSIX,
		 * input baud rate is set equal to the output baud rate
		 * when zero.
		 */
		if (t->c_ispeed == 0)
			t->c_ispeed = t->c_ospeed;

		/* Discard any unsupported bits. */
		t->c_iflag &= TTYSUP_IFLAG;
		t->c_oflag &= TTYSUP_OFLAG;
		t->c_lflag &= TTYSUP_LFLAG;
		t->c_cflag &= TTYSUP_CFLAG;

		/* Set terminal flags through tcsetattr(). */
		if (cmd == TIOCSETAW || cmd == TIOCSETAF) {
			error = tty_drain(tp, 0);
			if (error)
				return (error);
			if (cmd == TIOCSETAF)
				tty_flush(tp, FREAD);
		}

		/*
		 * Only call param() when the flags really change.
		 */
		if ((t->c_cflag & CIGNORE) == 0 &&
		    (tp->t_termios.c_cflag != t->c_cflag ||
		    ((tp->t_termios.c_iflag ^ t->c_iflag) &
		    (IXON|IXOFF|IXANY)) ||
		    tp->t_termios.c_ispeed != t->c_ispeed ||
		    tp->t_termios.c_ospeed != t->c_ospeed)) {
			error = ttydevsw_param(tp, t);
			if (error)
				return (error);

			/* XXX: CLOCAL? */

			tp->t_termios.c_cflag = t->c_cflag & ~CIGNORE;
			tp->t_termios.c_ispeed = t->c_ispeed;
			tp->t_termios.c_ospeed = t->c_ospeed;

			/* Baud rate has changed - update watermarks. */
			error = tty_watermarks(tp);
			if (error)
				return (error);
		}

		/* Copy new non-device driver parameters. */
		tp->t_termios.c_iflag = t->c_iflag;
		tp->t_termios.c_oflag = t->c_oflag;
		tp->t_termios.c_lflag = t->c_lflag;
		memcpy(&tp->t_termios.c_cc, t->c_cc, sizeof t->c_cc);

		ttydisc_optimize(tp);

		if ((t->c_lflag & ICANON) == 0) {
			/*
			 * When in non-canonical mode, wake up all
			 * readers. Canonicalize any partial input. VMIN
			 * and VTIME could also be adjusted.
			 */
			ttyinq_canonicalize(&tp->t_inq);
			tty_wakeup(tp, FREAD);
		}

		/*
		 * For packet mode: notify the PTY consumer that VSTOP
		 * and VSTART may have been changed.
		 */
		if (tp->t_termios.c_iflag & IXON &&
		    tp->t_termios.c_cc[VSTOP] == CTRL('S') &&
		    tp->t_termios.c_cc[VSTART] == CTRL('Q'))
			ttydevsw_pktnotify(tp, TIOCPKT_DOSTOP);
		else
			ttydevsw_pktnotify(tp, TIOCPKT_NOSTOP);
		return (0);
	}
	case TIOCGETD:
		/* For compatibility - we only support TTYDISC. */
		*(int *)data = TTYDISC;
		return (0);
	case TIOCGPGRP:
		if (!tty_is_ctty(tp, td->td_proc))
			return (ENOTTY);

		if (tp->t_pgrp != NULL)
			*(int *)data = tp->t_pgrp->pg_id;
		else
			*(int *)data = NO_PID;
		return (0);
	case TIOCGSID:
		if (!tty_is_ctty(tp, td->td_proc))
			return (ENOTTY);

		MPASS(tp->t_session);
		*(int *)data = tp->t_session->s_sid;
		return (0);
	case TIOCSCTTY: {
		struct proc *p = td->td_proc;

		/* XXX: This looks awful. */
		tty_unlock(tp);
		sx_xlock(&proctree_lock);
		tty_lock(tp);

		if (!SESS_LEADER(p)) {
			/* Only the session leader may do this. */
			sx_xunlock(&proctree_lock);
			return (EPERM);
		}

		if (tp->t_session != NULL && tp->t_session == p->p_session) {
			/* This is already our controlling TTY. */
			sx_xunlock(&proctree_lock);
			return (0);
		}

		if (p->p_session->s_ttyp != NULL ||
		    (tp->t_session != NULL && tp->t_session->s_ttyvp != NULL &&
		    tp->t_session->s_ttyvp->v_type != VBAD)) {
			/*
			 * There is already a relation between a TTY and
			 * a session, or the caller is not the session
			 * leader.
			 *
			 * Allow the TTY to be stolen when the vnode is
			 * invalid, but the reference to the TTY is
			 * still active.  This allows immediate reuse of
			 * TTYs of which the session leader has been
			 * killed or the TTY revoked.
			 */
			sx_xunlock(&proctree_lock);
			return (EPERM);
		}

		/* Connect the session to the TTY. */
		tp->t_session = p->p_session;
		tp->t_session->s_ttyp = tp;
		tp->t_sessioncnt++;
		sx_xunlock(&proctree_lock);

		/* Assign foreground process group. */
		tp->t_pgrp = p->p_pgrp;
		PROC_LOCK(p);
		p->p_flag |= P_CONTROLT;
		PROC_UNLOCK(p);

		return (0);
	}
	case TIOCSPGRP: {
		struct pgrp *pg;

		/*
		 * XXX: Temporarily unlock the TTY to locate the process
		 * group. This code would be lot nicer if we would ever
		 * decompose proctree_lock.
		 */
		tty_unlock(tp);
		sx_slock(&proctree_lock);
		pg = pgfind(*(int *)data);
		if (pg != NULL)
			PGRP_UNLOCK(pg);
		if (pg == NULL || pg->pg_session != td->td_proc->p_session) {
			sx_sunlock(&proctree_lock);
			tty_lock(tp);
			return (EPERM);
		}
		tty_lock(tp);

		/*
		 * Determine if this TTY is the controlling TTY after
		 * relocking the TTY.
		 */
		if (!tty_is_ctty(tp, td->td_proc)) {
			sx_sunlock(&proctree_lock);
			return (ENOTTY);
		}
		tp->t_pgrp = pg;
		sx_sunlock(&proctree_lock);

		/* Wake up the background process groups. */
		cv_broadcast(&tp->t_bgwait);
		return (0);
	}
	case TIOCFLUSH: {
		int flags = *(int *)data;

		if (flags == 0)
			flags = (FREAD|FWRITE);
		else
			flags &= (FREAD|FWRITE);
		tty_flush(tp, flags);
		return (0);
	}
	case TIOCDRAIN:
		/* Drain TTY output. */
		return tty_drain(tp, 0);
	case TIOCGDRAINWAIT:
		*(int *)data = tp->t_drainwait;
		return (0);
	case TIOCSDRAINWAIT:
		error = priv_check(td, PRIV_TTY_DRAINWAIT);
		if (error == 0)
			tp->t_drainwait = *(int *)data;
		return (error);
	case TIOCCONS:
		/* Set terminal as console TTY. */
		if (*(int *)data) {
			error = priv_check(td, PRIV_TTY_CONSOLE);
			if (error)
				return (error);

			/*
			 * XXX: constty should really need to be locked!
			 * XXX: allow disconnected constty's to be stolen!
			 */

			if (constty == tp)
				return (0);
			if (constty != NULL)
				return (EBUSY);

			tty_unlock(tp);
			constty_set(tp);
			tty_lock(tp);
		} else if (constty == tp) {
			constty_clear();
		}
		return (0);
	case TIOCGWINSZ:
		/* Obtain window size. */
		*(struct winsize*)data = tp->t_winsize;
		return (0);
	case TIOCSWINSZ:
		/* Set window size. */
		tty_set_winsize(tp, data);
		return (0);
	case TIOCEXCL:
		tp->t_flags |= TF_EXCLUDE;
		return (0);
	case TIOCNXCL:
		tp->t_flags &= ~TF_EXCLUDE;
		return (0);
	case TIOCSTOP:
		tp->t_flags |= TF_STOPPED;
		ttydevsw_pktnotify(tp, TIOCPKT_STOP);
		return (0);
	case TIOCSTART:
		tp->t_flags &= ~TF_STOPPED;
		ttydevsw_outwakeup(tp);
		ttydevsw_pktnotify(tp, TIOCPKT_START);
		return (0);
	case TIOCSTAT:
		tty_info(tp);
		return (0);
	case TIOCSTI:
		if ((fflag & FREAD) == 0 && priv_check(td, PRIV_TTY_STI))
			return (EPERM);
		if (!tty_is_ctty(tp, td->td_proc) &&
		    priv_check(td, PRIV_TTY_STI))
			return (EACCES);
		ttydisc_rint(tp, *(char *)data, 0);
		ttydisc_rint_done(tp);
		return (0);
	}

#ifdef COMPAT_43TTY
	return tty_ioctl_compat(tp, cmd, data, fflag, td);
#else /* !COMPAT_43TTY */
	return (ENOIOCTL);
#endif /* COMPAT_43TTY */
}