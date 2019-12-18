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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_char ;
struct tty {scalar_t__ t_ospeed; int t_state; struct com_s* t_sc; } ;
struct termios {scalar_t__ c_ispeed; scalar_t__ c_ospeed; int c_cflag; int* c_cc; int c_iflag; int c_lflag; int c_oflag; } ;
struct com_s {int channel_control; int* cor; int state; int last_modem_status; int intr_enable; int /*<<< orphan*/ * ibufold; int /*<<< orphan*/  mcr_rts; int /*<<< orphan*/  mcr_image; int /*<<< orphan*/  mcr_rts_reg; int /*<<< orphan*/  gfrcr_image; } ;

/* Variables and functions */
 int BRKINT ; 
 int CCTS_OFLOW ; 
 int CD1400_CCR_CMDCHANCTL ; 
 int CD1400_CCR_CMDCORCHG ; 
 int CD1400_CCR_COR1 ; 
 int CD1400_CCR_COR2 ; 
 int CD1400_CCR_COR3 ; 
 int CD1400_CCR_RCVDIS ; 
 int CD1400_CCR_RCVEN ; 
 int CD1400_CCR_XMTEN ; 
 int /*<<< orphan*/  CD1400_COR1 ; 
 int CD1400_COR1_CS5 ; 
 int CD1400_COR1_CS6 ; 
 int CD1400_COR1_CS7 ; 
 int CD1400_COR1_CS8 ; 
 int CD1400_COR1_NOINPCK ; 
 int CD1400_COR1_PARNORMAL ; 
 int CD1400_COR1_PARODD ; 
 int CD1400_COR1_STOP2 ; 
 int /*<<< orphan*/  CD1400_COR2 ; 
 int CD1400_COR2_CCTS_OFLOW ; 
 int CD1400_COR2_IXANY ; 
 int CD1400_COR2_IXOFF ; 
 int /*<<< orphan*/  CD1400_COR3 ; 
 int CD1400_COR3_FCT ; 
 int CD1400_COR3_SCD12 ; 
 int CD1400_COR3_SCD34 ; 
 int /*<<< orphan*/  CD1400_COR4 ; 
 int CD1400_COR4_ICRNL ; 
 int CD1400_COR4_IGNBRK ; 
 int CD1400_COR4_IGNCR ; 
 int CD1400_COR4_INLCR ; 
 int CD1400_COR4_NOBRKINT ; 
 int CD1400_COR4_PFO_DISCARD ; 
 int CD1400_COR4_PFO_ESC ; 
 int CD1400_COR4_PFO_EXCEPTION ; 
 int CD1400_COR4_PFO_NUL ; 
 int /*<<< orphan*/  CD1400_COR5 ; 
 int CD1400_COR5_ISTRIP ; 
 int CD1400_COR5_LNEXT ; 
 int CD1400_COR5_OCRNL ; 
 int CD1400_COR5_ONLCR ; 
 int /*<<< orphan*/  CD1400_MCOR1 ; 
 int CD1400_MCOR1_CDzd ; 
 int CD1400_MCOR1_CTSzd ; 
 int /*<<< orphan*/  CD1400_MCOR2 ; 
 int CD1400_MCOR2_CDod ; 
 int CD1400_MCOR2_CTSod ; 
 int CD1400_MSVR2_CTS ; 
 int /*<<< orphan*/  CD1400_RBPR ; 
 int /*<<< orphan*/  CD1400_RCOR ; 
 int /*<<< orphan*/  CD1400_RTPR ; 
 int /*<<< orphan*/  CD1400_SCHR1 ; 
 int /*<<< orphan*/  CD1400_SCHR2 ; 
 int /*<<< orphan*/  CD1400_SCHR3 ; 
 int /*<<< orphan*/  CD1400_SCHR4 ; 
 int /*<<< orphan*/  CD1400_SRER ; 
 int CD1400_SRER_TXMPTY ; 
 int CD1400_SRER_TXRDY ; 
 int /*<<< orphan*/  CD1400_TBPR ; 
 int /*<<< orphan*/  CD1400_TCOR ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int CREAD ; 
 int CRTS_IFLOW ; 
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 int CSIZE ; 
 int CSTOPB ; 
 int CS_BUSY ; 
 int CS_CTS_OFLOW ; 
 int CS_ODEVREADY ; 
 int CS_RTS_IFLOW ; 
 int CS_TTGO ; 
 int /*<<< orphan*/  CY_CLOCK (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNBRK ; 
 int IGNCR ; 
 int IGNPAR ; 
 int INLCR ; 
 int INPCK ; 
 int ISTRIP ; 
 int IXANY ; 
 int IXOFF ; 
 int MIN_RTP ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int OCRNL ; 
 int ONLCR ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int RxFifoThreshold ; 
 int /*<<< orphan*/  SER_DTR ; 
 int TS_TTSTOP ; 
 size_t VINTR ; 
 size_t VMIN ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 size_t VSUSP ; 
 size_t VTIME ; 
 int _POSIX_VDISABLE ; 
 int /*<<< orphan*/  cd1400_channel_cmd (struct com_s*,int) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  cyintr1 (struct com_s*) ; 
 int /*<<< orphan*/  cymodem (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cysetwater (struct com_s*,scalar_t__) ; 
 int cyspeed (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cystart (struct tty*) ; 
 int /*<<< orphan*/  disc_optim (struct tty*,struct termios*,struct com_s*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int howmany (int,scalar_t__) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
cyparam(struct tty *tp, struct termios *t)
{
	int		bits;
	int		cflag;
	struct com_s	*com;
	u_char		cor_change;
	u_long		cy_clock;
	int		idivisor;
	int		iflag;
	int		iprescaler;
	int		itimeout;
	int		odivisor;
	int		oprescaler;
	u_char		opt;
	int		s;

	com = tp->t_sc;

	/* check requested parameters */
	cy_clock = CY_CLOCK(com->gfrcr_image);
	idivisor = cyspeed(t->c_ispeed, cy_clock, &iprescaler);
	if (idivisor <= 0)
		return (EINVAL);
	odivisor = cyspeed(t->c_ospeed != 0 ? t->c_ospeed : tp->t_ospeed,
			    cy_clock, &oprescaler);
	if (odivisor <= 0)
		return (EINVAL);

	/* parameters are OK, convert them to the com struct and the device */
	s = spltty();
	if (t->c_ospeed == 0)
		(void)cymodem(tp, 0, SER_DTR);
	else
		(void)cymodem(tp, SER_DTR, 0);

	(void) cysetwater(com, t->c_ispeed);

	/* XXX we don't actually change the speed atomically. */

	cd_setreg(com, CD1400_RBPR, idivisor);
	cd_setreg(com, CD1400_RCOR, iprescaler);
	cd_setreg(com, CD1400_TBPR, odivisor);
	cd_setreg(com, CD1400_TCOR, oprescaler);

	/*
	 * channel control
	 *	receiver enable
	 *	transmitter enable (always set)
	 */
	cflag = t->c_cflag;
	opt = CD1400_CCR_CMDCHANCTL | CD1400_CCR_XMTEN
	      | (cflag & CREAD ? CD1400_CCR_RCVEN : CD1400_CCR_RCVDIS);
	if (opt != com->channel_control) {
		com->channel_control = opt;
		cd1400_channel_cmd(com, opt);
	}

#ifdef Smarts
	/* set special chars */
	/* XXX if one is _POSIX_VDISABLE, can't use some others */
	if (t->c_cc[VSTOP] != _POSIX_VDISABLE)
		cd_setreg(com, CD1400_SCHR1, t->c_cc[VSTOP]);
	if (t->c_cc[VSTART] != _POSIX_VDISABLE)
		cd_setreg(com, CD1400_SCHR2, t->c_cc[VSTART]);
	if (t->c_cc[VINTR] != _POSIX_VDISABLE)
		cd_setreg(com, CD1400_SCHR3, t->c_cc[VINTR]);
	if (t->c_cc[VSUSP] != _POSIX_VDISABLE)
		cd_setreg(com, CD1400_SCHR4, t->c_cc[VSUSP]);
#endif

	/*
	 * set channel option register 1 -
	 *	parity mode
	 *	stop bits
	 *	char length
	 */
	opt = 0;
	/* parity */
	if (cflag & PARENB) {
		if (cflag & PARODD)
			opt |= CD1400_COR1_PARODD;
		opt |= CD1400_COR1_PARNORMAL;
	}
	iflag = t->c_iflag;
	if (!(iflag & INPCK))
		opt |= CD1400_COR1_NOINPCK;
	bits = 1 + 1;
	/* stop bits */
	if (cflag & CSTOPB) {
		++bits;
		opt |= CD1400_COR1_STOP2;
	}
	/* char length */
	switch (cflag & CSIZE) {
	case CS5:
		bits += 5;
		opt |= CD1400_COR1_CS5;
		break;
	case CS6:
		bits += 6;
		opt |= CD1400_COR1_CS6;
		break;
	case CS7:
		bits += 7;
		opt |= CD1400_COR1_CS7;
		break;
	default:
		bits += 8;
		opt |= CD1400_COR1_CS8;
		break;
	}
	cor_change = 0;
	if (opt != com->cor[0]) {
		cor_change |= CD1400_CCR_COR1;
		cd_setreg(com, CD1400_COR1, com->cor[0] = opt);
	}

	/*
	 * Set receive time-out period, normally to max(one char time, 5 ms).
	 */
	itimeout = howmany(1000 * bits, t->c_ispeed);
#ifdef SOFT_HOTCHAR
#define	MIN_RTP		1
#else
#define	MIN_RTP		5
#endif
	if (itimeout < MIN_RTP)
		itimeout = MIN_RTP;
	if (!(t->c_lflag & ICANON) && t->c_cc[VMIN] != 0 && t->c_cc[VTIME] != 0
	    && t->c_cc[VTIME] * 10 > itimeout)
		itimeout = t->c_cc[VTIME] * 10;
	if (itimeout > 255)
		itimeout = 255;
	cd_setreg(com, CD1400_RTPR, itimeout);

	/*
	 * set channel option register 2 -
	 *	flow control
	 */
	opt = 0;
#ifdef Smarts
	if (iflag & IXANY)
		opt |= CD1400_COR2_IXANY;
	if (iflag & IXOFF)
		opt |= CD1400_COR2_IXOFF;
#endif
#ifndef SOFT_CTS_OFLOW
	if (cflag & CCTS_OFLOW)
		opt |= CD1400_COR2_CCTS_OFLOW;
#endif
	critical_enter();
	COM_LOCK();
	if (opt != com->cor[1]) {
		cor_change |= CD1400_CCR_COR2;
		cd_setreg(com, CD1400_COR2, com->cor[1] = opt);
	}
	COM_UNLOCK();
	critical_exit();

	/*
	 * set channel option register 3 -
	 *	receiver FIFO interrupt threshold
	 *	flow control
	 */
	opt = RxFifoThreshold;
#ifdef Smarts
	if (t->c_lflag & ICANON)
		opt |= CD1400_COR3_SCD34;	/* detect INTR & SUSP chars */
	if (iflag & IXOFF)
		/* detect and transparently handle START and STOP chars */
		opt |= CD1400_COR3_FCT | CD1400_COR3_SCD12;
#endif
	if (opt != com->cor[2]) {
		cor_change |= CD1400_CCR_COR3;
		cd_setreg(com, CD1400_COR3, com->cor[2] = opt);
	}

	/* notify the CD1400 if COR1-3 have changed */
	if (cor_change)
		cd1400_channel_cmd(com, CD1400_CCR_CMDCORCHG | cor_change);

	/*
	 * set channel option register 4 -
	 *	CR/NL processing
	 *	break processing
	 *	received exception processing
	 */
	opt = 0;
	if (iflag & IGNCR)
		opt |= CD1400_COR4_IGNCR;
#ifdef Smarts
	/*
	 * we need a new ttyinput() for this, as we don't want to
	 * have ICRNL && INLCR being done in both layers, or to have
	 * synchronisation problems
	 */
	if (iflag & ICRNL)
		opt |= CD1400_COR4_ICRNL;
	if (iflag & INLCR)
		opt |= CD1400_COR4_INLCR;
#endif
	if (iflag & IGNBRK)
		opt |= CD1400_COR4_IGNBRK | CD1400_COR4_NOBRKINT;
	/*
	 * The `-ignbrk -brkint parmrk' case is not handled by the hardware,
	 * so only tell the hardware about -brkint if -parmrk.
	 */
	if (!(iflag & (BRKINT | PARMRK)))
		opt |= CD1400_COR4_NOBRKINT;
#if 0
	/* XXX using this "intelligence" breaks reporting of overruns. */
	if (iflag & IGNPAR)
		opt |= CD1400_COR4_PFO_DISCARD;
	else {
		if (iflag & PARMRK)
			opt |= CD1400_COR4_PFO_ESC;
		else
			opt |= CD1400_COR4_PFO_NUL;
	}
#else
	opt |= CD1400_COR4_PFO_EXCEPTION;
#endif
	cd_setreg(com, CD1400_COR4, opt);

	/*
	 * set channel option register 5 -
	 */
	opt = 0;
	if (iflag & ISTRIP)
		opt |= CD1400_COR5_ISTRIP;
	if (t->c_iflag & IEXTEN)
		/* enable LNEXT (e.g. ctrl-v quoting) handling */
		opt |= CD1400_COR5_LNEXT;
#ifdef Smarts
	if (t->c_oflag & ONLCR)
		opt |= CD1400_COR5_ONLCR;
	if (t->c_oflag & OCRNL)
		opt |= CD1400_COR5_OCRNL;
#endif
	cd_setreg(com, CD1400_COR5, opt);

	/*
	 * We always generate modem status change interrupts for CD changes.
	 * Among other things, this is necessary to track TS_CARR_ON for
	 * pstat to print even when the driver doesn't care.  CD changes
	 * should be rare so interrupts for them are not worth extra code to
	 * avoid.  We avoid interrupts for other modem status changes (except
	 * for CTS changes when SOFT_CTS_OFLOW is configured) since this is
	 * simplest and best.
	 */

	/*
	 * set modem change option register 1
	 *	generate modem interrupts on which 1 -> 0 input transitions
	 *	also controls auto-DTR output flow-control, which we don't use
	 */
	opt = CD1400_MCOR1_CDzd;
#ifdef SOFT_CTS_OFLOW
	if (cflag & CCTS_OFLOW)
		opt |= CD1400_MCOR1_CTSzd;
#endif
	cd_setreg(com, CD1400_MCOR1, opt);

	/*
	 * set modem change option register 2
	 *	generate modem interrupts on specific 0 -> 1 input transitions
	 */
	opt = CD1400_MCOR2_CDod;
#ifdef SOFT_CTS_OFLOW
	if (cflag & CCTS_OFLOW)
		opt |= CD1400_MCOR2_CTSod;
#endif
	cd_setreg(com, CD1400_MCOR2, opt);

	/*
	 * XXX should have done this long ago, but there is too much state
	 * to change all atomically.
	 */
	critical_enter();
	COM_LOCK();

	com->state &= ~CS_TTGO;
	if (!(tp->t_state & TS_TTSTOP))
		com->state |= CS_TTGO;
	if (cflag & CRTS_IFLOW) {
		com->state |= CS_RTS_IFLOW;
		/*
		 * If CS_RTS_IFLOW just changed from off to on, the change
		 * needs to be propagated to CD1400_MSVR1_RTS.  This isn't urgent,
		 * so do it later by calling cystart() instead of repeating
		 * a lot of code from cystart() here.
		 */
	} else if (com->state & CS_RTS_IFLOW) {
		com->state &= ~CS_RTS_IFLOW;
		/*
		 * CS_RTS_IFLOW just changed from on to off.  Force CD1400_MSVR1_RTS
		 * on here, since cystart() won't do it later.
		 */
		cd_setreg(com, com->mcr_rts_reg,
			  com->mcr_image |= com->mcr_rts);
	}

	/*
	 * Set up state to handle output flow control.
	 * XXX - worth handling MDMBUF (DCD) flow control at the lowest level?
	 * Now has 10+ msec latency, while CTS flow has 50- usec latency.
	 */
	com->state |= CS_ODEVREADY;
#ifdef SOFT_CTS_OFLOW
	com->state &= ~CS_CTS_OFLOW;
	if (cflag & CCTS_OFLOW) {
		com->state |= CS_CTS_OFLOW;
		if (!(com->last_modem_status & CD1400_MSVR2_CTS))
			com->state &= ~CS_ODEVREADY;
	}
#endif
	/* XXX shouldn't call functions while intrs are disabled. */
	disc_optim(tp, t, com);
#if 0
	/*
	 * Recover from fiddling with CS_TTGO.  We used to call cyintr1()
	 * unconditionally, but that defeated the careful discarding of
	 * stale input in cyopen().
	 */
	if (com->state >= (CS_BUSY | CS_TTGO))
		cyintr1(com);
#endif
	if (com->state >= (CS_BUSY | CS_TTGO | CS_ODEVREADY)) {
		if (!(com->intr_enable & CD1400_SRER_TXRDY))
			cd_setreg(com, CD1400_SRER,
				  com->intr_enable
				  = (com->intr_enable & ~CD1400_SRER_TXMPTY)
				    | CD1400_SRER_TXRDY);
	} else {
		if (com->intr_enable & CD1400_SRER_TXRDY)
			cd_setreg(com, CD1400_SRER,
				  com->intr_enable
				  = (com->intr_enable & ~CD1400_SRER_TXRDY)
				    | CD1400_SRER_TXMPTY);
	}

	COM_UNLOCK();
	critical_exit();
	splx(s);
	cystart(tp);
	if (com->ibufold != NULL) {
		free(com->ibufold, M_DEVBUF);
		com->ibufold = NULL;
	}
	return (0);
}