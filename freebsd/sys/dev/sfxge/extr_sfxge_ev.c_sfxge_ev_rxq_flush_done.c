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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sfxge_softc {struct sfxge_evq** evq; struct sfxge_rxq** rxq; } ;
struct sfxge_rxq {unsigned int index; } ;
struct sfxge_evq {unsigned int index; scalar_t__ init_state; int /*<<< orphan*/  common; struct sfxge_softc* sc; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_SW_EV_RX_QFLUSH_DONE ; 
 int /*<<< orphan*/  efx_ev_qpost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_rx_qflush_done (struct sfxge_rxq*) ; 
 int /*<<< orphan*/  sfxge_sw_ev_rxq_magic (int /*<<< orphan*/ ,struct sfxge_rxq*) ; 

__attribute__((used)) static boolean_t
sfxge_ev_rxq_flush_done(void *arg, uint32_t rxq_index)
{
	struct sfxge_evq *evq;
	struct sfxge_softc *sc;
	struct sfxge_rxq *rxq;
	unsigned int index;
	uint16_t magic;

	evq = (struct sfxge_evq *)arg;
	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	sc = evq->sc;
	rxq = sc->rxq[rxq_index];

	KASSERT(rxq != NULL, ("rxq == NULL"));

	/* Resend a software event on the correct queue */
	index = rxq->index;
	if (index == evq->index) {
		sfxge_rx_qflush_done(rxq);
		return (B_FALSE);
	}

	evq = sc->evq[index];
	magic = sfxge_sw_ev_rxq_magic(SFXGE_SW_EV_RX_QFLUSH_DONE, rxq);

	KASSERT(evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq not started"));
	efx_ev_qpost(evq->common, magic);

	return (B_FALSE);
}