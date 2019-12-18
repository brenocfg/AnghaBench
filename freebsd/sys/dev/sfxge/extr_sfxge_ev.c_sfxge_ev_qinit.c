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
struct sfxge_softc {int txq_entries; struct sfxge_evq** evq; int /*<<< orphan*/  dev; scalar_t__ rxq_entries; } ;
struct sfxge_evq {unsigned int index; int /*<<< orphan*/  init_state; int /*<<< orphan*/  buf_base_id; void* entries; int /*<<< orphan*/  txq; int /*<<< orphan*/ * txqs; int /*<<< orphan*/  mem; struct sfxge_softc* sc; } ;
typedef  int /*<<< orphan*/  efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_EVQ_NBUFS (void*) ; 
 int /*<<< orphan*/  EFX_EVQ_SIZE (void*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* ROUNDUP_POW_OF_TWO (scalar_t__) ; 
 int /*<<< orphan*/  SFXGE_EVQ_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_DESTROY (struct sfxge_evq*) ; 
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_INIT (struct sfxge_evq*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SFXGE_EVQ_UNINITIALIZED ; 
 unsigned int SFXGE_RX_SCALE_MAX ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sfxge_evq*,int /*<<< orphan*/ ) ; 
 struct sfxge_evq* malloc (int,int /*<<< orphan*/ ,int) ; 
 int sfxge_dma_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 
 int sfxge_evq_stat_init (struct sfxge_evq*) ; 
 int /*<<< orphan*/  sfxge_sram_buf_tbl_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sfxge_ev_qinit(struct sfxge_softc *sc, unsigned int index)
{
	struct sfxge_evq *evq;
	efsys_mem_t *esmp;
	int rc;

	KASSERT(index < SFXGE_RX_SCALE_MAX, ("index >= SFXGE_RX_SCALE_MAX"));

	evq = malloc(sizeof(struct sfxge_evq), M_SFXGE, M_ZERO | M_WAITOK);
	evq->sc = sc;
	evq->index = index;
	sc->evq[index] = evq;
	esmp = &evq->mem;

	/* Build an event queue with room for one event per tx and rx buffer,
	 * plus some extra for link state events and MCDI completions.
	 * There are three tx queues in the first event queue and one in
	 * other.
	 */
	if (index == 0)
		evq->entries =
			ROUNDUP_POW_OF_TWO(sc->rxq_entries +
					   3 * sc->txq_entries +
					   128);
	else
		evq->entries =
			ROUNDUP_POW_OF_TWO(sc->rxq_entries +
					   sc->txq_entries +
					   128);

	/* Initialise TX completion list */
	evq->txqs = &evq->txq;

	/* Allocate DMA space. */
	if ((rc = sfxge_dma_alloc(sc, EFX_EVQ_SIZE(evq->entries), esmp)) != 0)
		return (rc);

	/* Allocate buffer table entries. */
	sfxge_sram_buf_tbl_alloc(sc, EFX_EVQ_NBUFS(evq->entries),
				 &evq->buf_base_id);

	SFXGE_EVQ_LOCK_INIT(evq, device_get_nameunit(sc->dev), index);

	evq->init_state = SFXGE_EVQ_INITIALIZED;

#if EFSYS_OPT_QSTATS
	rc = sfxge_evq_stat_init(evq);
	if (rc != 0)
		goto fail_evq_stat_init;
#endif

	return (0);

#if EFSYS_OPT_QSTATS
fail_evq_stat_init:
	evq->init_state = SFXGE_EVQ_UNINITIALIZED;
	SFXGE_EVQ_LOCK_DESTROY(evq);
	sfxge_dma_free(esmp);
	sc->evq[index] = NULL;
	free(evq, M_SFXGE);

	return (rc);
#endif
}