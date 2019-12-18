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
typedef  int u_char ;
struct sbni_softc {int state; scalar_t__ tx_frameno; int /*<<< orphan*/  ifp; int /*<<< orphan*/  timer_ticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_LEVEL_START_TICKS ; 
 int /*<<< orphan*/  CSR0 ; 
 int EN_INT ; 
 int FL_PREV_OK ; 
 int RC_RDY ; 
 int TR_RDY ; 
 int TR_REQ ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int recv_frame (struct sbni_softc*) ; 
 int sbni_inb (struct sbni_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbni_outb (struct sbni_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_frame (struct sbni_softc*) ; 

__attribute__((used)) static void
handle_channel(struct sbni_softc *sc)
{
	int req_ans;
	u_char csr0;

	sbni_outb(sc, CSR0, (sbni_inb(sc, CSR0) & ~EN_INT) | TR_REQ);

	sc->timer_ticks = CHANGE_LEVEL_START_TICKS;
	for (;;) {
		csr0 = sbni_inb(sc, CSR0);
		if ((csr0 & (RC_RDY | TR_RDY)) == 0)
			break;

		req_ans = !(sc->state & FL_PREV_OK);

		if (csr0 & RC_RDY)
			req_ans = recv_frame(sc);

		/*
		 * TR_RDY always equals 1 here because we have owned the marker,
		 * and we set TR_REQ when disabled interrupts
		 */
		csr0 = sbni_inb(sc, CSR0);
		if ((csr0 & TR_RDY) == 0 || (csr0 & RC_RDY) != 0)
			if_printf(sc->ifp, "internal error!\n");

		/* if state & FL_NEED_RESEND != 0 then tx_frameno != 0 */
		if (req_ans || sc->tx_frameno != 0)
			send_frame(sc);
		else {
			/* send the marker without any data */
			sbni_outb(sc, CSR0, sbni_inb(sc, CSR0) & ~TR_REQ);
		}
	}

	sbni_outb(sc, CSR0, sbni_inb(sc, CSR0) | EN_INT);
}