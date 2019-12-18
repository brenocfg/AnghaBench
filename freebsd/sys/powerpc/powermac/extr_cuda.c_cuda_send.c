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
typedef  int /*<<< orphan*/  uint8_t ;
struct cuda_softc {scalar_t__ sc_state; scalar_t__ sc_polling; int /*<<< orphan*/  sc_mutex; scalar_t__ sc_waiting; int /*<<< orphan*/  sc_outq; int /*<<< orphan*/  sc_freeq; int /*<<< orphan*/  sc_dev; } ;
struct cuda_packet {int len; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CUDA_NOTREADY ; 
 struct cuda_packet* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cuda_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  cuda_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuda_send_outbound (struct cuda_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_q ; 

__attribute__((used)) static int
cuda_send(void *cookie, int poll, int length, uint8_t *msg)
{
	struct cuda_softc *sc = cookie;
	device_t dev = sc->sc_dev;
	struct cuda_packet *pkt;

	if (sc->sc_state == CUDA_NOTREADY)
		return (-1);

	mtx_lock(&sc->sc_mutex);

	pkt = STAILQ_FIRST(&sc->sc_freeq);
	if (pkt == NULL) {
		mtx_unlock(&sc->sc_mutex);
		return (-1);
	}

	pkt->len = length - 1;
	pkt->type = msg[0];
	memcpy(pkt->data, &msg[1], pkt->len);

	STAILQ_REMOVE_HEAD(&sc->sc_freeq, pkt_q);
	STAILQ_INSERT_TAIL(&sc->sc_outq, pkt, pkt_q);

	/*
	 * If we already are sending a packet, we should bail now that this
	 * one has been added to the queue.
	 */

	if (sc->sc_waiting) {
		mtx_unlock(&sc->sc_mutex);
		return (0);
	}

	cuda_send_outbound(sc);
	mtx_unlock(&sc->sc_mutex);

	if (sc->sc_polling || poll || cold)
		cuda_poll(dev);

	return (0);
}