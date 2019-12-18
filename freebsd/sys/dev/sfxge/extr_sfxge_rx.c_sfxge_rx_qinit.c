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
struct sfxge_softc {unsigned int rxq_count; int rxq_entries; struct sfxge_evq** evq; struct sfxge_rxq** rxq; } ;
struct sfxge_rxq {unsigned int index; int entries; int ptr_mask; int /*<<< orphan*/  init_state; int /*<<< orphan*/  refill_callout; void* queue; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/  mem; int /*<<< orphan*/  refill_threshold; struct sfxge_softc* sc; } ;
struct sfxge_rx_sw_desc {int dummy; } ;
struct sfxge_evq {int dummy; } ;
typedef  int /*<<< orphan*/  efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_RXQ_NBUFS (int) ; 
 int /*<<< orphan*/  EFX_RXQ_SIZE (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RX_REFILL_THRESHOLD (int) ; 
 int /*<<< orphan*/  SFXGE_RXQ_INITIALIZED ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int sfxge_dma_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_lro_init (struct sfxge_rxq*) ; 
 int /*<<< orphan*/  sfxge_sram_buf_tbl_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sfxge_rx_qinit(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_rxq *rxq;
	struct sfxge_evq *evq;
	efsys_mem_t *esmp;
	int rc;

	KASSERT(index < sc->rxq_count, ("index >= %d", sc->rxq_count));

	rxq = malloc(sizeof(struct sfxge_rxq), M_SFXGE, M_ZERO | M_WAITOK);
	rxq->sc = sc;
	rxq->index = index;
	rxq->entries = sc->rxq_entries;
	rxq->ptr_mask = rxq->entries - 1;
	rxq->refill_threshold = RX_REFILL_THRESHOLD(rxq->entries);

	sc->rxq[index] = rxq;
	esmp = &rxq->mem;

	evq = sc->evq[index];

	/* Allocate and zero DMA space. */
	if ((rc = sfxge_dma_alloc(sc, EFX_RXQ_SIZE(sc->rxq_entries), esmp)) != 0)
		return (rc);

	/* Allocate buffer table entries. */
	sfxge_sram_buf_tbl_alloc(sc, EFX_RXQ_NBUFS(sc->rxq_entries),
				 &rxq->buf_base_id);

	/* Allocate the context array and the flow table. */
	rxq->queue = malloc(sizeof(struct sfxge_rx_sw_desc) * sc->rxq_entries,
	    M_SFXGE, M_WAITOK | M_ZERO);
	sfxge_lro_init(rxq);

	callout_init(&rxq->refill_callout, 1);

	rxq->init_state = SFXGE_RXQ_INITIALIZED;

	return (0);
}