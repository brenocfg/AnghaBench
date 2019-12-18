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
struct termios {int c_cflag; int /*<<< orphan*/  c_ispeed; int /*<<< orphan*/  c_ospeed; } ;
struct tty {struct termios t_termios; } ;
struct nmdmpart {int np_rate; int np_credits; struct nmdmpart* np_other; int /*<<< orphan*/  np_callout; struct tty* np_tty; } ;

/* Variables and functions */
 int CDSR_OFLOW ; 
 int QS ; 
 int /*<<< orphan*/  bits_per_char (struct termios*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nmdmpart*) ; 
 int hz ; 
 int imax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmdm_timeout ; 
 struct nmdmpart* tty_softc (struct tty*) ; 

__attribute__((used)) static int
nmdm_param(struct tty *tp, struct termios *t)
{
	struct nmdmpart *np = tty_softc(tp);
	struct tty *tp2;
	int bpc, rate, speed, i;

	tp2 = np->np_other->np_tty;

	if (!((t->c_cflag | tp2->t_termios.c_cflag) & CDSR_OFLOW)) {
		np->np_rate = 0;
		np->np_other->np_rate = 0;
		return (0);
	}

	/*
	 * DSRFLOW one either side enables rate-simulation for both
	 * directions.
	 * NB: the two directions may run at different rates.
	 */

	/* Find the larger of the number of bits transmitted */
	bpc = imax(bits_per_char(t), bits_per_char(&tp2->t_termios));

	for (i = 0; i < 2; i++) {
		/* Use the slower of our receive and their transmit rate */
		speed = imin(tp2->t_termios.c_ospeed, t->c_ispeed);
		if (speed == 0) {
			np->np_rate = 0;
			np->np_other->np_rate = 0;
			return (0);
		}

		speed <<= QS;			/* [bit/sec, scaled] */
		speed /= bpc;			/* [char/sec, scaled] */
		rate = (hz << QS) / speed;	/* [hz per callout] */
		if (rate == 0)
			rate = 1;

		speed *= rate;
		speed /= hz;			/* [(char/sec)/tick, scaled */

		np->np_credits = speed;
		np->np_rate = rate;
		callout_reset(&np->np_callout, rate, nmdm_timeout, np);

		/*
		 * swap pointers for second pass so the other end gets
		 * updated as well.
		 */
		np = np->np_other;
		t = &tp2->t_termios;
		tp2 = tp;
	}

	return (0);
}