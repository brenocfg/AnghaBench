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
struct tty {int dummy; } ;
struct pts_softc {int pts_pkt; } ;

/* Variables and functions */
#define  TIOCPKT_DOSTOP 131 
#define  TIOCPKT_NOSTOP 130 
#define  TIOCPKT_START 129 
#define  TIOCPKT_STOP 128 
 int /*<<< orphan*/  ptsdrv_outwakeup (struct tty*) ; 
 struct pts_softc* tty_softc (struct tty*) ; 

__attribute__((used)) static void
ptsdrv_pktnotify(struct tty *tp, char event)
{
	struct pts_softc *psc = tty_softc(tp);

	/*
	 * Clear conflicting flags.
	 */

	switch (event) {
	case TIOCPKT_STOP:
		psc->pts_pkt &= ~TIOCPKT_START;
		break;
	case TIOCPKT_START:
		psc->pts_pkt &= ~TIOCPKT_STOP;
		break;
	case TIOCPKT_NOSTOP:
		psc->pts_pkt &= ~TIOCPKT_DOSTOP;
		break;
	case TIOCPKT_DOSTOP:
		psc->pts_pkt &= ~TIOCPKT_NOSTOP;
		break;
	}

	psc->pts_pkt |= event;
	ptsdrv_outwakeup(tp);
}