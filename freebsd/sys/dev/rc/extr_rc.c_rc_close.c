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
struct tty {int t_cflag; int t_state; struct rc_chans* t_sc; } ;
struct rc_softc {int dummy; } ;
struct rc_chans {int rc_flags; int rc_msvr; struct rc_softc* rc_rcb; scalar_t__ rc_chan; scalar_t__ rc_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCRCMD (struct rc_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR_ResetChan ; 
 int /*<<< orphan*/  CD180_CAR ; 
 int /*<<< orphan*/  CD180_IER ; 
 int CLOCAL ; 
 int HUPCL ; 
 int MSVR_CD ; 
 int RC_ACTOUT ; 
 int /*<<< orphan*/  SER_RTS ; 
 struct rc_softc** TSA_CARR_ON (struct tty*) ; 
 int TS_ISOPEN ; 
 int /*<<< orphan*/  WAITFORCCR (struct rc_softc*,scalar_t__) ; 
 int /*<<< orphan*/  rc_modem (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcout (struct rc_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  ttydtrwaitstart (struct tty*) ; 
 int /*<<< orphan*/  wakeup (struct rc_softc**) ; 

__attribute__((used)) static void
rc_close(struct tty *tp)
{
	struct rc_chans *rc;
	struct rc_softc *sc;
	int s;

	rc = tp->t_sc;
	sc = rc->rc_rcb;
	s = spltty();
	rcout(sc, CD180_CAR, rc->rc_chan);

	/* Disable rx/tx intrs */
	rcout(sc, CD180_IER, rc->rc_ier = 0);
	if (   (tp->t_cflag & HUPCL)
	    || (!(rc->rc_flags & RC_ACTOUT)
	       && !(rc->rc_msvr & MSVR_CD)
	       && !(tp->t_cflag & CLOCAL))
	    || !(tp->t_state & TS_ISOPEN)
	   ) {
		CCRCMD(sc, rc->rc_chan, CCR_ResetChan);
		WAITFORCCR(sc, rc->rc_chan);
		(void) rc_modem(tp, SER_RTS, 0);
		ttydtrwaitstart(tp);
	}
	rc->rc_flags &= ~RC_ACTOUT;
	wakeup( &rc->rc_rcb);  /* wake bi */
	wakeup(TSA_CARR_ON(tp));
	(void) splx(s);
}