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
struct cuda_softc {int sc_waiting; scalar_t__ sc_state; int /*<<< orphan*/ * sc_out; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_freeq; int /*<<< orphan*/  sc_outq; scalar_t__ sc_sent; scalar_t__ sc_out_length; int /*<<< orphan*/  sc_mutex; } ;
struct cuda_packet {scalar_t__ len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ CUDA_IDLE ; 
 scalar_t__ CUDA_OUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct cuda_packet* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuda_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_ack_off (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_intr_state (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_out (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_tip (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_write_reg (struct cuda_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_q ; 
 int /*<<< orphan*/  vSR ; 

__attribute__((used)) static void
cuda_send_outbound(struct cuda_softc *sc)
{
	struct cuda_packet *pkt;

	mtx_assert(&sc->sc_mutex, MA_OWNED);

	pkt = STAILQ_FIRST(&sc->sc_outq);
	if (pkt == NULL)
		return;

	sc->sc_out_length = pkt->len + 1;
	memcpy(sc->sc_out, &pkt->type, pkt->len + 1);
	sc->sc_sent = 0;

	STAILQ_REMOVE_HEAD(&sc->sc_outq, pkt_q);
	STAILQ_INSERT_TAIL(&sc->sc_freeq, pkt, pkt_q);

	sc->sc_waiting = 1;

	cuda_poll(sc->sc_dev);

	DELAY(150);

	if (sc->sc_state == CUDA_IDLE && !cuda_intr_state(sc)) {
		sc->sc_state = CUDA_OUT;
		cuda_out(sc);
		cuda_write_reg(sc, vSR, sc->sc_out[0]);
		cuda_ack_off(sc);
		cuda_tip(sc);
	}
}