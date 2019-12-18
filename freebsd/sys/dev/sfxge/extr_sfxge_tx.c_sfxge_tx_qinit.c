#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sfxge_tx_dpl {int /*<<< orphan*/  std_put_hiwat; int /*<<< orphan*/  std_get_hiwat; int /*<<< orphan*/  std_get_non_tcp_count; int /*<<< orphan*/  std_get_count; int /*<<< orphan*/  std_get; int /*<<< orphan*/ * std_getp; int /*<<< orphan*/  std_get_non_tcp_max; int /*<<< orphan*/  std_get_max; int /*<<< orphan*/  std_put_max; } ;
struct sfxge_txq {int entries; int ptr_mask; int type; unsigned int evq_index; int /*<<< orphan*/  packet_dma_tag; TYPE_2__* stmp; TYPE_2__* pend_desc; int /*<<< orphan*/  init_state; struct sfxge_tx_dpl dpl; int /*<<< orphan*/  buf_base_id; int /*<<< orphan*/  mem; struct sfxge_softc* sc; } ;
struct sfxge_tx_mapping {int dummy; } ;
struct sfxge_softc {int txq_entries; int /*<<< orphan*/  dev; struct sysctl_oid* txqs_node; int /*<<< orphan*/  parent_dma_tag; struct sfxge_evq** evq; struct sfxge_txq** txq; int /*<<< orphan*/  enp; } ;
struct sfxge_evq {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  enum sfxge_txq_type { ____Placeholder_sfxge_txq_type } sfxge_txq_type ;
struct TYPE_4__ {int /*<<< orphan*/  enc_tx_dma_desc_size_max; int /*<<< orphan*/  enc_tx_dma_desc_boundary; } ;
typedef  TYPE_1__ efx_nic_cfg_t ;
typedef  int /*<<< orphan*/  efx_desc_t ;
typedef  int /*<<< orphan*/  efsys_mem_t ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_STATS ; 
 int /*<<< orphan*/  EFX_TXQ_NBUFS (int) ; 
 int /*<<< orphan*/  EFX_TXQ_SIZE (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SFXGE_TXQ_INITIALIZED ; 
 int SFXGE_TXQ_IP_TCP_UDP_CKSUM ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_INIT (struct sfxge_txq*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SFXGE_TX_MAPPING_MAX_SEG ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* efx_nic_cfg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int sfxge_dma_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_sram_buf_tbl_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_tx_dpl_get_max ; 
 int /*<<< orphan*/  sfxge_tx_dpl_get_non_tcp_max ; 
 int /*<<< orphan*/  sfxge_tx_dpl_put_max ; 
 int sfxge_txq_stat_init (struct sfxge_txq*,struct sysctl_oid*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int tso_init (struct sfxge_txq*) ; 

__attribute__((used)) static int
sfxge_tx_qinit(struct sfxge_softc *sc, unsigned int txq_index,
	       enum sfxge_txq_type type, unsigned int evq_index)
{
	const efx_nic_cfg_t *encp = efx_nic_cfg_get(sc->enp);
	char name[16];
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->dev);
	struct sysctl_oid *txq_node;
	struct sfxge_txq *txq;
	struct sfxge_evq *evq;
	struct sfxge_tx_dpl *stdp;
	struct sysctl_oid *dpl_node;
	efsys_mem_t *esmp;
	unsigned int nmaps;
	int rc;

	txq = malloc(sizeof(struct sfxge_txq), M_SFXGE, M_ZERO | M_WAITOK);
	txq->sc = sc;
	txq->entries = sc->txq_entries;
	txq->ptr_mask = txq->entries - 1;

	sc->txq[txq_index] = txq;
	esmp = &txq->mem;

	evq = sc->evq[evq_index];

	/* Allocate and zero DMA space for the descriptor ring. */
	if ((rc = sfxge_dma_alloc(sc, EFX_TXQ_SIZE(sc->txq_entries), esmp)) != 0)
		return (rc);

	/* Allocate buffer table entries. */
	sfxge_sram_buf_tbl_alloc(sc, EFX_TXQ_NBUFS(sc->txq_entries),
				 &txq->buf_base_id);

	/* Create a DMA tag for packet mappings. */
	if (bus_dma_tag_create(sc->parent_dma_tag, 1,
	    encp->enc_tx_dma_desc_boundary,
	    MIN(0x3FFFFFFFFFFFUL, BUS_SPACE_MAXADDR), BUS_SPACE_MAXADDR, NULL,
	    NULL, 0x11000, SFXGE_TX_MAPPING_MAX_SEG,
	    encp->enc_tx_dma_desc_size_max, 0, NULL, NULL,
	    &txq->packet_dma_tag) != 0) {
		device_printf(sc->dev, "Couldn't allocate txq DMA tag\n");
		rc = ENOMEM;
		goto fail;
	}

	/* Allocate pending descriptor array for batching writes. */
	txq->pend_desc = malloc(sizeof(efx_desc_t) * sc->txq_entries,
				M_SFXGE, M_ZERO | M_WAITOK);

	/* Allocate and initialise mbuf DMA mapping array. */
	txq->stmp = malloc(sizeof(struct sfxge_tx_mapping) * sc->txq_entries,
	    M_SFXGE, M_ZERO | M_WAITOK);
	for (nmaps = 0; nmaps < sc->txq_entries; nmaps++) {
		rc = bus_dmamap_create(txq->packet_dma_tag, 0,
				       &txq->stmp[nmaps].map);
		if (rc != 0)
			goto fail2;
	}

	snprintf(name, sizeof(name), "%u", txq_index);
	txq_node = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(sc->txqs_node),
				   OID_AUTO, name, CTLFLAG_RD, NULL, "");
	if (txq_node == NULL) {
		rc = ENOMEM;
		goto fail_txq_node;
	}

	if (type == SFXGE_TXQ_IP_TCP_UDP_CKSUM &&
	    (rc = tso_init(txq)) != 0)
		goto fail3;

	/* Initialize the deferred packet list. */
	stdp = &txq->dpl;
	stdp->std_put_max = sfxge_tx_dpl_put_max;
	stdp->std_get_max = sfxge_tx_dpl_get_max;
	stdp->std_get_non_tcp_max = sfxge_tx_dpl_get_non_tcp_max;
	stdp->std_getp = &stdp->std_get;

	SFXGE_TXQ_LOCK_INIT(txq, device_get_nameunit(sc->dev), txq_index);

	dpl_node = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(txq_node), OID_AUTO,
				   "dpl", CTLFLAG_RD, NULL,
				   "Deferred packet list statistics");
	if (dpl_node == NULL) {
		rc = ENOMEM;
		goto fail_dpl_node;
	}

	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(dpl_node), OID_AUTO,
			"get_count", CTLFLAG_RD | CTLFLAG_STATS,
			&stdp->std_get_count, 0, "");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(dpl_node), OID_AUTO,
			"get_non_tcp_count", CTLFLAG_RD | CTLFLAG_STATS,
			&stdp->std_get_non_tcp_count, 0, "");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(dpl_node), OID_AUTO,
			"get_hiwat", CTLFLAG_RD | CTLFLAG_STATS,
			&stdp->std_get_hiwat, 0, "");
	SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(dpl_node), OID_AUTO,
			"put_hiwat", CTLFLAG_RD | CTLFLAG_STATS,
			&stdp->std_put_hiwat, 0, "");

	rc = sfxge_txq_stat_init(txq, txq_node);
	if (rc != 0)
		goto fail_txq_stat_init;

	txq->type = type;
	txq->evq_index = evq_index;
	txq->init_state = SFXGE_TXQ_INITIALIZED;

	return (0);

fail_txq_stat_init:
fail_dpl_node:
fail3:
fail_txq_node:
	free(txq->pend_desc, M_SFXGE);
fail2:
	while (nmaps-- != 0)
		bus_dmamap_destroy(txq->packet_dma_tag, txq->stmp[nmaps].map);
	free(txq->stmp, M_SFXGE);
	bus_dma_tag_destroy(txq->packet_dma_tag);

fail:
	sfxge_dma_free(esmp);

	return (rc);
}