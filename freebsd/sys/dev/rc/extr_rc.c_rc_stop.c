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
typedef  int /*<<< orphan*/  u_char ;
struct tty {int t_state; struct rc_chans* t_sc; } ;
struct rc_softc {int sc_scheduled_event; int /*<<< orphan*/  sc_dev; } ;
struct rc_chans {int /*<<< orphan*/  rc_flags; int /*<<< orphan*/ * rc_ibuf; int /*<<< orphan*/ * rc_iptr; int /*<<< orphan*/ * rc_bufend; int /*<<< orphan*/  rc_chan; struct rc_softc* rc_rcb; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  RC_DORXFER ; 
 int RC_IBUFSIZE ; 
 int /*<<< orphan*/  RC_OSUSP ; 
 int TS_TTSTOP ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  rc_discard_output (struct rc_chans*) ; 

__attribute__((used)) static void
rc_stop(struct tty *tp, int rw)
{
	struct rc_softc *sc;
	struct rc_chans *rc;
	u_char *tptr, *eptr;

	rc = tp->t_sc;
	sc = rc->rc_rcb;
#ifdef RCDEBUG
	device_printf(sc->sc_dev, "channel %d: rc_stop %s%s\n",
	    rc->rc_chan, (rw & FWRITE)?"FWRITE ":"", (rw & FREAD)?"FREAD":"");
#endif
	if (rw & FWRITE)
		rc_discard_output(rc);
	critical_enter();
	if (rw & FREAD) {
		rc->rc_flags &= ~RC_DORXFER;
		eptr = rc->rc_iptr;
		if (rc->rc_bufend == &rc->rc_ibuf[2 * RC_IBUFSIZE]) {
			tptr = &rc->rc_ibuf[RC_IBUFSIZE];
			rc->rc_iptr = &rc->rc_ibuf[RC_IBUFSIZE];
		} else {
			tptr = rc->rc_ibuf;
			rc->rc_iptr = rc->rc_ibuf;
		}
		sc->sc_scheduled_event -= eptr - tptr;
	}
	if (tp->t_state & TS_TTSTOP)
		rc->rc_flags |= RC_OSUSP;
	else
		rc->rc_flags &= ~RC_OSUSP;
	critical_exit();
}