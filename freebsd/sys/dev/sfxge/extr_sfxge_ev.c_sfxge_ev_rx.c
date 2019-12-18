#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct sfxge_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  enp; } ;
struct sfxge_rxq {scalar_t__ init_state; int ptr_mask; int pending; int entries; scalar_t__ completed; struct sfxge_rx_sw_desc* queue; } ;
struct sfxge_rx_sw_desc {scalar_t__ flags; void* size; int /*<<< orphan*/  mbuf; } ;
struct sfxge_evq {scalar_t__ rx_done; scalar_t__ exception; struct sfxge_softc* sc; } ;
typedef  int boolean_t ;
struct TYPE_2__ {unsigned int enc_rx_batch_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ B_TRUE ; 
 scalar_t__ EFX_DISCARD ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 scalar_t__ SFXGE_EV_BATCH ; 
 scalar_t__ SFXGE_RXQ_STARTED ; 
 scalar_t__ SFXGE_RX_BATCH ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,unsigned int,void*) ; 
 TYPE_1__* efx_nic_cfg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch_read_many (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_ev_qcomplete (struct sfxge_evq*,int /*<<< orphan*/ ) ; 
 struct sfxge_rxq* sfxge_get_rxq_by_label (struct sfxge_evq*,int) ; 
 int /*<<< orphan*/  sfxge_schedule_reset (struct sfxge_softc*) ; 

__attribute__((used)) static boolean_t
sfxge_ev_rx(void *arg, uint32_t label, uint32_t id, uint32_t size,
	    uint16_t flags)
{
	struct sfxge_evq *evq;
	struct sfxge_softc *sc;
	struct sfxge_rxq *rxq;
	unsigned int stop;
	unsigned int delta;
	struct sfxge_rx_sw_desc *rx_desc;

	evq = arg;
	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	sc = evq->sc;

	if (evq->exception)
		goto done;

	rxq = sfxge_get_rxq_by_label(evq, label);
	if (__predict_false(rxq->init_state != SFXGE_RXQ_STARTED))
		goto done;

	stop = (id + 1) & rxq->ptr_mask;
	id = rxq->pending & rxq->ptr_mask;
	delta = (stop >= id) ? (stop - id) : (rxq->entries - id + stop);
	rxq->pending += delta;

	if (delta != 1) {
		if ((delta <= 0) ||
		    (delta > efx_nic_cfg_get(sc->enp)->enc_rx_batch_max)) {
			evq->exception = B_TRUE;

			device_printf(sc->dev, "RX completion out of order"
						  " (id=%#x delta=%u flags=%#x); resetting\n",
						  id, delta, flags);
			sfxge_schedule_reset(sc);

			goto done;
		}
	}

	rx_desc = &rxq->queue[id];

	prefetch_read_many(rx_desc->mbuf);

	for (; id != stop; id = (id + 1) & rxq->ptr_mask) {
		rx_desc = &rxq->queue[id];
		KASSERT(rx_desc->flags == EFX_DISCARD,
				("rx_desc->flags != EFX_DISCARD"));
		rx_desc->flags = flags;

		KASSERT(size < (1 << 16), ("size > (1 << 16)"));
		rx_desc->size = (uint16_t)size;
	}

	evq->rx_done++;

	if (rxq->pending - rxq->completed >= SFXGE_RX_BATCH)
		sfxge_ev_qcomplete(evq, B_FALSE);

done:
	return (evq->rx_done >= SFXGE_EV_BATCH);
}