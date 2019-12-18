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
struct tty {int t_state; struct rc_chans* t_sc; } ;
struct termios {int c_ospeed; int c_ispeed; int c_cflag; int c_iflag; int c_lflag; int* c_cc; } ;
struct rc_softc {int dummy; } ;
struct rc_chans {int rc_chan; int rc_flags; int rc_cor2; int rc_ier; int rc_msvr; struct rc_softc* rc_rcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCRCMD (struct rc_softc*,int,int) ; 
 int CCR_CORCHG1 ; 
 int CCR_CORCHG2 ; 
 int CCR_CORCHG3 ; 
 int CCR_RCVRDIS ; 
 int CCR_RCVREN ; 
 int CCR_ResetChan ; 
 int CCR_XMTREN ; 
 int CCTS_OFLOW ; 
 int /*<<< orphan*/  CD180_CAR ; 
 int /*<<< orphan*/  CD180_COR1 ; 
 int /*<<< orphan*/  CD180_COR2 ; 
 int /*<<< orphan*/  CD180_COR3 ; 
 int /*<<< orphan*/  CD180_IER ; 
 int /*<<< orphan*/  CD180_MCOR1 ; 
 int /*<<< orphan*/  CD180_MCOR2 ; 
 int CD180_NFIFO ; 
 int /*<<< orphan*/  CD180_RBPRH ; 
 int /*<<< orphan*/  CD180_RBPRL ; 
 int /*<<< orphan*/  CD180_RTPR ; 
 int /*<<< orphan*/  CD180_SCHR1 ; 
 int /*<<< orphan*/  CD180_SCHR2 ; 
 int /*<<< orphan*/  CD180_TBPRH ; 
 int /*<<< orphan*/  CD180_TBPRL ; 
 int CLOCAL ; 
 int COR1_2SB ; 
 int COR1_5BITS ; 
 int COR1_6BITS ; 
 int COR1_7BITS ; 
 int COR1_8BITS ; 
 int COR1_Ignore ; 
 int COR1_NORMPAR ; 
 int COR1_ODDP ; 
 int COR2_CtsAE ; 
 int COR2_IXM ; 
 int COR2_TxIBE ; 
 int COR3_FCT ; 
 int COR3_SCDE ; 
 int CREAD ; 
 int CRTS_IFLOW ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int EINVAL ; 
 int ICANON ; 
 int IER_CD ; 
 int IER_CTS ; 
 int IER_RxData ; 
 int IER_TxRdy ; 
 int INPCK ; 
 int IXANY ; 
 int IXOFF ; 
 int MCOR1_CDzd ; 
 int MCOR1_CTSzd ; 
 int MCOR2_CDod ; 
 int MCOR2_CTSod ; 
 int MSVR_CTS ; 
 int PARENB ; 
 int PARODD ; 
 int RC_BRD (int) ; 
 int RC_CTSFLOW ; 
 int RC_OSUSP ; 
 int RC_RTSFLOW ; 
 int RC_SEND_RDY ; 
 int /*<<< orphan*/  SER_DTR ; 
 int TS_BUSY ; 
 int TS_CAN_BYPASS_L_RINT ; 
 int TS_TTSTOP ; 
 size_t VMIN ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 size_t VTIME ; 
 int /*<<< orphan*/  WAITFORCCR (struct rc_softc*,int) ; 
 int _POSIX_VDISABLE ; 
 int /*<<< orphan*/  rc_modem (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcout (struct rc_softc*,int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  ttyldoptim (struct tty*) ; 

__attribute__((used)) static int
rc_param(struct tty *tp, struct termios *ts)
{
	struct rc_softc *sc;
	struct rc_chans *rc;
	int idivs, odivs, s, val, cflag, iflag, lflag, inpflow;

	if (   ts->c_ospeed < 0 || ts->c_ospeed > 76800
	    || ts->c_ispeed < 0 || ts->c_ispeed > 76800
	   )
		return (EINVAL);
	if (ts->c_ispeed == 0)
		ts->c_ispeed = ts->c_ospeed;
	odivs = RC_BRD(ts->c_ospeed);
	idivs = RC_BRD(ts->c_ispeed);

	rc = tp->t_sc;
	sc = rc->rc_rcb;
	s = spltty();

	/* Select channel */
	rcout(sc, CD180_CAR, rc->rc_chan);

	/* If speed == 0, hangup line */
	if (ts->c_ospeed == 0) {
		CCRCMD(sc, rc->rc_chan, CCR_ResetChan);
		WAITFORCCR(sc, rc->rc_chan);
		(void) rc_modem(tp, 0, SER_DTR);
	}

	tp->t_state &= ~TS_CAN_BYPASS_L_RINT;
	cflag = ts->c_cflag;
	iflag = ts->c_iflag;
	lflag = ts->c_lflag;

	if (idivs > 0) {
		rcout(sc, CD180_RBPRL, idivs & 0xFF);
		rcout(sc, CD180_RBPRH, idivs >> 8);
	}
	if (odivs > 0) {
		rcout(sc, CD180_TBPRL, odivs & 0xFF);
		rcout(sc, CD180_TBPRH, odivs >> 8);
	}

	/* set timeout value */
	if (ts->c_ispeed > 0) {
		int itm = ts->c_ispeed > 2400 ? 5 : 10000 / ts->c_ispeed + 1;

		if (   !(lflag & ICANON)
		    && ts->c_cc[VMIN] != 0 && ts->c_cc[VTIME] != 0
		    && ts->c_cc[VTIME] * 10 > itm)
			itm = ts->c_cc[VTIME] * 10;

		rcout(sc, CD180_RTPR, itm <= 255 ? itm : 255);
	}

	switch (cflag & CSIZE) {
		case CS5:       val = COR1_5BITS;      break;
		case CS6:       val = COR1_6BITS;      break;
		case CS7:       val = COR1_7BITS;      break;
		default:
		case CS8:       val = COR1_8BITS;      break;
	}
	if (cflag & PARENB) {
		val |= COR1_NORMPAR;
		if (cflag & PARODD)
			val |= COR1_ODDP;
		if (!(cflag & INPCK))
			val |= COR1_Ignore;
	} else
		val |= COR1_Ignore;
	if (cflag & CSTOPB)
		val |= COR1_2SB;
	rcout(sc, CD180_COR1, val);

	/* Set FIFO threshold */
	val = ts->c_ospeed <= 4800 ? 1 : CD180_NFIFO / 2;
	inpflow = 0;
	if (   (iflag & IXOFF)
	    && (   ts->c_cc[VSTOP] != _POSIX_VDISABLE
		&& (   ts->c_cc[VSTART] != _POSIX_VDISABLE
		    || (iflag & IXANY)
		   )
	       )
	   ) {
		inpflow = 1;
		val |= COR3_SCDE|COR3_FCT;
	}
	rcout(sc, CD180_COR3, val);

	/* Initialize on-chip automatic flow control */
	val = 0;
	rc->rc_flags &= ~(RC_CTSFLOW|RC_SEND_RDY);
	if (cflag & CCTS_OFLOW) {
		rc->rc_flags |= RC_CTSFLOW;
		val |= COR2_CtsAE;
	} else
		rc->rc_flags |= RC_SEND_RDY;
	if (tp->t_state & TS_TTSTOP)
		rc->rc_flags |= RC_OSUSP;
	else
		rc->rc_flags &= ~RC_OSUSP;
	if (cflag & CRTS_IFLOW)
		rc->rc_flags |= RC_RTSFLOW;
	else
		rc->rc_flags &= ~RC_RTSFLOW;

	if (inpflow) {
		if (ts->c_cc[VSTART] != _POSIX_VDISABLE)
			rcout(sc, CD180_SCHR1, ts->c_cc[VSTART]);
		rcout(sc, CD180_SCHR2, ts->c_cc[VSTOP]);
		val |= COR2_TxIBE;
		if (iflag & IXANY)
			val |= COR2_IXM;
	}

	rcout(sc, CD180_COR2, rc->rc_cor2 = val);

	CCRCMD(sc, rc->rc_chan, CCR_CORCHG1 | CCR_CORCHG2 | CCR_CORCHG3);

	ttyldoptim(tp);

	/* modem ctl */
	val = cflag & CLOCAL ? 0 : MCOR1_CDzd;
	if (cflag & CCTS_OFLOW)
		val |= MCOR1_CTSzd;
	rcout(sc, CD180_MCOR1, val);

	val = cflag & CLOCAL ? 0 : MCOR2_CDod;
	if (cflag & CCTS_OFLOW)
		val |= MCOR2_CTSod;
	rcout(sc, CD180_MCOR2, val);

	/* enable i/o and interrupts */
	CCRCMD(sc, rc->rc_chan,
		CCR_XMTREN | ((cflag & CREAD) ? CCR_RCVREN : CCR_RCVRDIS));
	WAITFORCCR(sc, rc->rc_chan);

	rc->rc_ier = cflag & CLOCAL ? 0 : IER_CD;
	if (cflag & CCTS_OFLOW)
		rc->rc_ier |= IER_CTS;
	if (cflag & CREAD)
		rc->rc_ier |= IER_RxData;
	if (tp->t_state & TS_BUSY)
		rc->rc_ier |= IER_TxRdy;
	if (ts->c_ospeed != 0)
		rc_modem(tp, SER_DTR, 0);
	if ((cflag & CCTS_OFLOW) && (rc->rc_msvr & MSVR_CTS))
		rc->rc_flags |= RC_SEND_RDY;
	rcout(sc, CD180_IER, rc->rc_ier);
	(void) splx(s);
	return 0;
}