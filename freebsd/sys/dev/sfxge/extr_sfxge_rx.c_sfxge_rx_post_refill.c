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
typedef  int /*<<< orphan*/  uint16_t ;
struct sfxge_softc {struct sfxge_evq** evq; } ;
struct sfxge_rxq {unsigned int index; scalar_t__ init_state; struct sfxge_softc* sc; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 scalar_t__ SFXGE_RXQ_STARTED ; 
 int /*<<< orphan*/  SFXGE_SW_EV_RX_QREFILL ; 
 int /*<<< orphan*/  efx_ev_qpost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_sw_ev_rxq_magic (int /*<<< orphan*/ ,struct sfxge_rxq*) ; 

__attribute__((used)) static void
sfxge_rx_post_refill(void *arg)
{
	struct sfxge_rxq *rxq = arg;
	struct sfxge_softc *sc;
	unsigned int index;
	struct sfxge_evq *evq;
	uint16_t magic;

	sc = rxq->sc;
	index = rxq->index;
	evq = sc->evq[index];
	magic = sfxge_sw_ev_rxq_magic(SFXGE_SW_EV_RX_QREFILL, rxq);

	/* This is guaranteed due to the start/stop order of rx and ev */
	KASSERT(evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq not started"));
	KASSERT(rxq->init_state == SFXGE_RXQ_STARTED,
	    ("rxq not started"));
	efx_ev_qpost(evq->common, magic);
}