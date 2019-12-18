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
typedef  int u_long ;
struct termios {void** c_cc; int /*<<< orphan*/  c_ispeed; int /*<<< orphan*/  c_ospeed; } ;
struct tty {int t_compatflags; struct termios t_termios; } ;
struct thread {int dummy; } ;
struct tchars {void* t_brkc; void* t_eofc; void* t_stopc; void* t_startc; void* t_quitc; void* t_intrc; } ;
struct sgttyb {int sg_flags; void* sg_kill; void* sg_erase; void* sg_ispeed; void* sg_ospeed; } ;
struct ltchars {void* t_lnextc; void* t_werasc; void* t_flushc; void* t_rprntc; void* t_dsuspc; void* t_suspc; } ;
typedef  void* cc_t ;
typedef  struct termios* caddr_t ;

/* Variables and functions */
 int ENOIOCTL ; 
#define  OTIOCCONS 141 
#define  OTIOCGETD 140 
#define  OTIOCSETD 139 
 int TIOCCONS ; 
#define  TIOCGETC 138 
#define  TIOCGETP 137 
#define  TIOCGLTC 136 
#define  TIOCLBIC 135 
#define  TIOCLBIS 134 
#define  TIOCLGET 133 
#define  TIOCLSET 132 
#define  TIOCSETC 131 
 int TIOCSETD ; 
#define  TIOCSETN 130 
#define  TIOCSETP 129 
#define  TIOCSLTC 128 
 size_t VDISCARD ; 
 size_t VDSUSP ; 
 size_t VEOF ; 
 size_t VEOL ; 
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
 int /*<<< orphan*/  compatspeeds ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int ttcompatgetflags (struct tty*) ; 
 void* ttcompatspeedtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttsetcompat (struct tty*,int*,struct termios*,struct termios*) ; 
 int tty_ioctl (struct tty*,int,struct termios*,int,struct thread*) ; 
 int /*<<< orphan*/  ttydebug ; 

int
tty_ioctl_compat(struct tty *tp, u_long com, caddr_t data, int fflag,
    struct thread *td)
{
	switch (com) {
	case TIOCSETP:
	case TIOCSETN:
	case TIOCSETC:
	case TIOCSLTC:
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET: {
		struct termios term;
		int error;

		term = tp->t_termios;
		if ((error = ttsetcompat(tp, &com, data, &term)) != 0)
			return error;
		return tty_ioctl(tp, com, &term, fflag, td);
	}
	case TIOCGETP: {
		struct sgttyb *sg = (struct sgttyb *)data;
		cc_t *cc = tp->t_termios.c_cc;

		sg->sg_ospeed = ttcompatspeedtab(tp->t_termios.c_ospeed,
		    compatspeeds);
		if (tp->t_termios.c_ispeed == 0)
			sg->sg_ispeed = sg->sg_ospeed;
		else
			sg->sg_ispeed = ttcompatspeedtab(tp->t_termios.c_ispeed,
			    compatspeeds);
		sg->sg_erase = cc[VERASE];
		sg->sg_kill = cc[VKILL];
		sg->sg_flags = tp->t_compatflags = ttcompatgetflags(tp);
		break;
	}
	case TIOCGETC: {
		struct tchars *tc = (struct tchars *)data;
		cc_t *cc = tp->t_termios.c_cc;

		tc->t_intrc = cc[VINTR];
		tc->t_quitc = cc[VQUIT];
		tc->t_startc = cc[VSTART];
		tc->t_stopc = cc[VSTOP];
		tc->t_eofc = cc[VEOF];
		tc->t_brkc = cc[VEOL];
		break;
	}
	case TIOCGLTC: {
		struct ltchars *ltc = (struct ltchars *)data;
		cc_t *cc = tp->t_termios.c_cc;

		ltc->t_suspc = cc[VSUSP];
		ltc->t_dsuspc = cc[VDSUSP];
		ltc->t_rprntc = cc[VREPRINT];
		ltc->t_flushc = cc[VDISCARD];
		ltc->t_werasc = cc[VWERASE];
		ltc->t_lnextc = cc[VLNEXT];
		break;
	}
	case TIOCLGET:
		tp->t_compatflags =
		 (ttcompatgetflags(tp) & 0xffff0000UL)
		   | (tp->t_compatflags & 0xffff);
		*(int *)data = tp->t_compatflags>>16;
		if (ttydebug)
			printf("CLGET: returning %x\n", *(int *)data);
		break;

	case OTIOCGETD:
		*(int *)data = 2;
		break;

	case OTIOCSETD: {
		int ldisczero = 0;

		return (tty_ioctl(tp, TIOCSETD,
			*(int *)data == 2 ? (caddr_t)&ldisczero : data,
			fflag, td));
	    }

	case OTIOCCONS: {
		int one = 1;

		return (tty_ioctl(tp, TIOCCONS, (caddr_t)&one, fflag, td));
	}

	default:
		return (ENOIOCTL);
	}
	return (0);
}