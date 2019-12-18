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
typedef  int uint8_t ;
struct cuda_softc {int sc_state; int sc_waiting; size_t sc_sent; int* sc_out; int sc_received; size_t sc_out_length; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_inq; int /*<<< orphan*/  sc_freeq; void** sc_in; } ;
struct cuda_packet {int /*<<< orphan*/  len; int /*<<< orphan*/  data; void* type; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
#define  CUDA_IDLE 131 
#define  CUDA_IN 130 
#define  CUDA_NOTREADY 129 
#define  CUDA_OUT 128 
 int /*<<< orphan*/  DELAY (int) ; 
 struct cuda_packet* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuda_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_ack_off (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_idle (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_in (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_intr_state (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_out (struct cuda_softc*) ; 
 void* cuda_read_reg (struct cuda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_send_inbound (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_send_outbound (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_tip (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_toggle_ack (struct cuda_softc*) ; 
 int /*<<< orphan*/  cuda_write_reg (struct cuda_softc*,int /*<<< orphan*/ ,int) ; 
 struct cuda_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_q ; 
 int /*<<< orphan*/  vIFR ; 
 int /*<<< orphan*/  vSR ; 
 int vSR_INT ; 

__attribute__((used)) static void
cuda_intr(void *arg)
{
	device_t        dev;
	struct cuda_softc *sc;

	int i, ending, restart_send, process_inbound;
	uint8_t reg;

        dev = (device_t)arg;
	sc = device_get_softc(dev);

	mtx_lock(&sc->sc_mutex);

	restart_send = 0;
	process_inbound = 0;
	reg = cuda_read_reg(sc, vIFR);
	if ((reg & vSR_INT) != vSR_INT) {
		mtx_unlock(&sc->sc_mutex);
		return;
	}

	cuda_write_reg(sc, vIFR, 0x7f);	/* Clear interrupt */

switch_start:
	switch (sc->sc_state) {
	case CUDA_IDLE:
		/*
		 * This is an unexpected packet, so grab the first (dummy)
		 * byte, set up the proper vars, and tell the chip we are
		 * starting to receive the packet by setting the TIP bit.
		 */
		sc->sc_in[1] = cuda_read_reg(sc, vSR);

		if (cuda_intr_state(sc) == 0) {
			/* must have been a fake start */

			if (sc->sc_waiting) {
				/* start over */
				DELAY(150);
				sc->sc_state = CUDA_OUT;
				sc->sc_sent = 0;
				cuda_out(sc);
				cuda_write_reg(sc, vSR, sc->sc_out[1]);
				cuda_ack_off(sc);
				cuda_tip(sc);
			}
			break;
		}

		cuda_in(sc);
		cuda_tip(sc);

		sc->sc_received = 1;
		sc->sc_state = CUDA_IN;
		break;

	case CUDA_IN:
		sc->sc_in[sc->sc_received] = cuda_read_reg(sc, vSR);
		ending = 0;

		if (sc->sc_received > 255) {
			/* bitch only once */
			if (sc->sc_received == 256) {
				device_printf(dev,"input overflow\n");
				ending = 1;
			}
		} else
			sc->sc_received++;

		/* intr off means this is the last byte (end of frame) */
		if (cuda_intr_state(sc) == 0) {
			ending = 1;
		} else {
			cuda_toggle_ack(sc);			
		}
		
		if (ending == 1) {	/* end of message? */
			struct cuda_packet *pkt;

			/* reset vars and signal the end of this frame */
			cuda_idle(sc);

			/* Queue up the packet */
			pkt = STAILQ_FIRST(&sc->sc_freeq);
			if (pkt != NULL) {
				/* If we have a free packet, process it */

				pkt->len = sc->sc_received - 2;
				pkt->type = sc->sc_in[1];
				memcpy(pkt->data, &sc->sc_in[2], pkt->len);

				STAILQ_REMOVE_HEAD(&sc->sc_freeq, pkt_q);
				STAILQ_INSERT_TAIL(&sc->sc_inq, pkt, pkt_q);

				process_inbound = 1;
			}

			sc->sc_state = CUDA_IDLE;
			sc->sc_received = 0;

			/*
			 * If there is something waiting to be sent out,
			 * set everything up and send the first byte.
			 */
			if (sc->sc_waiting == 1) {
				DELAY(1500);	/* required */
				sc->sc_sent = 0;
				sc->sc_state = CUDA_OUT;

				/*
				 * If the interrupt is on, we were too slow
				 * and the chip has already started to send
				 * something to us, so back out of the write
				 * and start a read cycle.
				 */
				if (cuda_intr_state(sc)) {
					cuda_in(sc);
					cuda_idle(sc);
					sc->sc_sent = 0;
					sc->sc_state = CUDA_IDLE;
					sc->sc_received = 0;
					DELAY(150);
					goto switch_start;
				}

				/*
				 * If we got here, it's ok to start sending
				 * so load the first byte and tell the chip
				 * we want to send.
				 */
				cuda_out(sc);
				cuda_write_reg(sc, vSR,
				    sc->sc_out[sc->sc_sent]);
				cuda_ack_off(sc);
				cuda_tip(sc);
			}
		}
		break;

	case CUDA_OUT:
		i = cuda_read_reg(sc, vSR);	/* reset SR-intr in IFR */

		sc->sc_sent++;
		if (cuda_intr_state(sc)) {	/* ADB intr low during write */
			cuda_in(sc);	/* make sure SR is set to IN */
			cuda_idle(sc);
			sc->sc_sent = 0;	/* must start all over */
			sc->sc_state = CUDA_IDLE;	/* new state */
			sc->sc_received = 0;
			sc->sc_waiting = 1;	/* must retry when done with
						 * read */
			DELAY(150);
			goto switch_start;	/* process next state right
						 * now */
			break;
		}
		if (sc->sc_out_length == sc->sc_sent) {	/* check for done */
			sc->sc_waiting = 0;	/* done writing */
			sc->sc_state = CUDA_IDLE;	/* signal bus is idle */
			cuda_in(sc);
			cuda_idle(sc);
		} else {
			/* send next byte */
			cuda_write_reg(sc, vSR, sc->sc_out[sc->sc_sent]);
			cuda_toggle_ack(sc);	/* signal byte ready to
							 * shift */
		}
		break;

	case CUDA_NOTREADY:
		break;

	default:
		break;
	}

	mtx_unlock(&sc->sc_mutex);

	if (process_inbound)
		cuda_send_inbound(sc);

	mtx_lock(&sc->sc_mutex);
	/* If we have another packet waiting, set it up */
	if (!sc->sc_waiting && sc->sc_state == CUDA_IDLE)
		cuda_send_outbound(sc);

	mtx_unlock(&sc->sc_mutex);

}