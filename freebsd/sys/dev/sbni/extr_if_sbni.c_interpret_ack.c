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
typedef  scalar_t__ u_int ;
struct sbni_softc {int state; scalar_t__ outpos; scalar_t__ pktlen; int /*<<< orphan*/  maxframe; scalar_t__ framelen; scalar_t__ tx_frameno; } ;

/* Variables and functions */
 int FL_NEED_RESEND ; 
 int FL_WAIT_ACK ; 
 scalar_t__ FRAME_SENT_OK ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  prepare_to_send (struct sbni_softc*) ; 
 int /*<<< orphan*/  send_complete (struct sbni_softc*) ; 

__attribute__((used)) static void
interpret_ack(struct sbni_softc *sc, u_int ack)
{
	if (ack == FRAME_SENT_OK) {
		sc->state &= ~FL_NEED_RESEND;

		if (sc->state & FL_WAIT_ACK) {
			sc->outpos += sc->framelen;

			if (--sc->tx_frameno) {
				sc->framelen = min(
				    sc->maxframe, sc->pktlen - sc->outpos);
			} else {
				send_complete(sc);
				prepare_to_send(sc);
			}
		}
	}

	sc->state &= ~FL_WAIT_ACK;
}