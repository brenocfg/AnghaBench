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
typedef  int u_long ;
struct TYPE_2__ {void* c_ospeed; void* c_ispeed; } ;
struct tty {int t_compatflags; TYPE_1__ t_termios; } ;
struct termios {char* c_cc; void* c_ospeed; void* c_ispeed; } ;
struct tchars {char t_intrc; char t_quitc; char t_startc; char t_stopc; char t_eofc; char t_brkc; } ;
struct sgttyb {int sg_ispeed; int sg_ospeed; char sg_erase; char sg_kill; int sg_flags; } ;
struct ltchars {char t_suspc; char t_dsuspc; char t_rprntc; char t_flushc; char t_werasc; char t_lnextc; } ;
typedef  char cc_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_SPEED ; 
#define  TIOCLBIC 134 
#define  TIOCLBIS 133 
#define  TIOCLSET 132 
 int TIOCSETA ; 
 int TIOCSETAF ; 
#define  TIOCSETC 131 
#define  TIOCSETN 130 
#define  TIOCSETP 129 
#define  TIOCSLTC 128 
 size_t VDISCARD ; 
 size_t VDSUSP ; 
 size_t VEOF ; 
 size_t VEOL ; 
 size_t VEOL2 ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VLNEXT ; 
 size_t VQUIT ; 
 size_t VREPRINT ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 size_t VSUSP ; 
 size_t VWERASE ; 
 char _POSIX_VDISABLE ; 
 void** compatspcodes ; 
 int /*<<< orphan*/  compatspeeds ; 
 int ttcompatgetflags (struct tty*) ; 
 int /*<<< orphan*/  ttcompatsetflags (struct tty*,struct termios*) ; 
 int /*<<< orphan*/  ttcompatsetlflags (struct tty*,struct termios*) ; 
 int ttcompatspeedtab (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ttsetcompat(struct tty *tp, u_long *com, caddr_t data, struct termios *term)
{
	switch (*com) {
	case TIOCSETP:
	case TIOCSETN: {
		struct sgttyb *sg = (struct sgttyb *)data;
		int speed;

		if ((speed = sg->sg_ispeed) > MAX_SPEED || speed < 0)
			return(EINVAL);
		else if (speed != ttcompatspeedtab(tp->t_termios.c_ispeed,
		    compatspeeds))
			term->c_ispeed = compatspcodes[speed];
		else
			term->c_ispeed = tp->t_termios.c_ispeed;
		if ((speed = sg->sg_ospeed) > MAX_SPEED || speed < 0)
			return(EINVAL);
		else if (speed != ttcompatspeedtab(tp->t_termios.c_ospeed,
		    compatspeeds))
			term->c_ospeed = compatspcodes[speed];
		else
			term->c_ospeed = tp->t_termios.c_ospeed;
		term->c_cc[VERASE] = sg->sg_erase;
		term->c_cc[VKILL] = sg->sg_kill;
		tp->t_compatflags = (tp->t_compatflags&0xffff0000) |
		    (sg->sg_flags&0xffff);
		ttcompatsetflags(tp, term);
		*com = (*com == TIOCSETP) ? TIOCSETAF : TIOCSETA;
		break;
	}
	case TIOCSETC: {
		struct tchars *tc = (struct tchars *)data;
		cc_t *cc;

		cc = term->c_cc;
		cc[VINTR] = tc->t_intrc;
		cc[VQUIT] = tc->t_quitc;
		cc[VSTART] = tc->t_startc;
		cc[VSTOP] = tc->t_stopc;
		cc[VEOF] = tc->t_eofc;
		cc[VEOL] = tc->t_brkc;
		if (tc->t_brkc == (char)_POSIX_VDISABLE)
			cc[VEOL2] = _POSIX_VDISABLE;
		*com = TIOCSETA;
		break;
	}
	case TIOCSLTC: {
		struct ltchars *ltc = (struct ltchars *)data;
		cc_t *cc;

		cc = term->c_cc;
		cc[VSUSP] = ltc->t_suspc;
		cc[VDSUSP] = ltc->t_dsuspc;
		cc[VREPRINT] = ltc->t_rprntc;
		cc[VDISCARD] = ltc->t_flushc;
		cc[VWERASE] = ltc->t_werasc;
		cc[VLNEXT] = ltc->t_lnextc;
		*com = TIOCSETA;
		break;
	}
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
		if (*com == TIOCLSET)
			tp->t_compatflags = (tp->t_compatflags&0xffff) |
			    *(int *)data<<16;
		else {
			tp->t_compatflags = (ttcompatgetflags(tp)&0xffff0000) |
			    (tp->t_compatflags&0xffff);
			if (*com == TIOCLBIS)
				tp->t_compatflags |= *(int *)data<<16;
			else
				tp->t_compatflags &= ~(*(int *)data<<16);
		}
		ttcompatsetlflags(tp, term);
		*com = TIOCSETA;
		break;
	}
	return 0;
}