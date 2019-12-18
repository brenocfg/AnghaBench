#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  void* uint16_t ;
struct tx_port_stats {int dummy; } ;
struct rx_port_stats {int dummy; } ;
struct ctx_hw_stats {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  idi_size; scalar_t__ idi_vaddr; int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; } ;
struct TYPE_9__ {int filter_id; TYPE_4__ mc_list; TYPE_4__ rss_hash_key_tbl; TYPE_4__ rss_grp_tbl; int /*<<< orphan*/  rss_hash_key; int /*<<< orphan*/  flags; scalar_t__ mc_list_count; int /*<<< orphan*/  rx_mask; void* lb_rule; void* cos_rule; void* def_ring_grp; void* flow_id; void* id; } ;
struct bnxt_softc {int nrxqsets; TYPE_6__* rx_cp_rings; TYPE_6__* rx_rings; TYPE_6__* ag_rings; TYPE_6__* grp_info; TYPE_4__ rx_stats; TYPE_4__ hw_rx_port_stats; TYPE_4__ hw_tx_port_stats; TYPE_3__ vnic_info; TYPE_1__* scctx; int /*<<< orphan*/  dev; void* tx_port_stats; void* rx_port_stats; } ;
struct bnxt_ring {int dummy; } ;
struct bnxt_grp_info {int dummy; } ;
struct bnxt_full_tpa_start {int dummy; } ;
struct bnxt_cp_ring {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  void* caddr_t ;
struct TYPE_8__ {int id; int doorbell; void* phys_id; void* paddr; void* vaddr; int /*<<< orphan*/  ring_size; struct bnxt_softc* softc; } ;
struct TYPE_11__ {int id; int doorbell; struct TYPE_11__* tpa_start; TYPE_2__ ring; void* cp_ring_id; void* phys_id; void* ag_ring_id; void* rx_ring_id; scalar_t__ stats_ctx_id; scalar_t__ stats_ctx; void* grp_id; void* paddr; void* vaddr; int /*<<< orphan*/  ring_size; struct bnxt_softc* softc; } ;
struct TYPE_7__ {int /*<<< orphan*/ * isc_nrxd; } ;

/* Variables and functions */
 int BNXT_MAX_MC_ADDRS ; 
 scalar_t__ BNXT_PF (struct bnxt_softc*) ; 
 int BNXT_PORT_STAT_PADDING ; 
 int /*<<< orphan*/  BNXT_VNIC_FLAG_DEFAULT ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_BCAST ; 
 scalar_t__ HWRM_NA_SIGNATURE ; 
 int HW_HASH_INDEX_SIZE ; 
 int HW_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int RX_TPA_START_CMPL_AGG_ID_MASK ; 
 int RX_TPA_START_CMPL_AGG_ID_SFT ; 
 int /*<<< orphan*/  bnxt_create_port_stats_sysctls (struct bnxt_softc*) ; 
 int /*<<< orphan*/  bnxt_create_rx_sysctls (struct bnxt_softc*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int iflib_dma_alloc (int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_dma_free (TYPE_4__*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_rx_queues_alloc(if_ctx_t ctx, caddr_t *vaddrs,
    uint64_t *paddrs, int nrxqs, int nrxqsets)
{
	struct bnxt_softc *softc;
	int i;
	int rc;

	softc = iflib_get_softc(ctx);

	softc->rx_cp_rings = malloc(sizeof(struct bnxt_cp_ring) * nrxqsets,
	    M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!softc->rx_cp_rings) {
		device_printf(iflib_get_dev(ctx),
		    "unable to allocate RX completion rings\n");
		rc = ENOMEM;
		goto cp_alloc_fail;
	}
	softc->rx_rings = malloc(sizeof(struct bnxt_ring) * nrxqsets,
	    M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!softc->rx_rings) {
		device_printf(iflib_get_dev(ctx),
		    "unable to allocate RX rings\n");
		rc = ENOMEM;
		goto ring_alloc_fail;
	}
	softc->ag_rings = malloc(sizeof(struct bnxt_ring) * nrxqsets,
	    M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!softc->ag_rings) {
		device_printf(iflib_get_dev(ctx),
		    "unable to allocate aggregation rings\n");
		rc = ENOMEM;
		goto ag_alloc_fail;
	}
	softc->grp_info = malloc(sizeof(struct bnxt_grp_info) * nrxqsets,
	    M_DEVBUF, M_NOWAIT | M_ZERO);
	if (!softc->grp_info) {
		device_printf(iflib_get_dev(ctx),
		    "unable to allocate ring groups\n");
		rc = ENOMEM;
		goto grp_alloc_fail;
	}

	rc = iflib_dma_alloc(ctx, sizeof(struct ctx_hw_stats) * nrxqsets,
	    &softc->rx_stats, 0);
	if (rc)
		goto hw_stats_alloc_fail;
	bus_dmamap_sync(softc->rx_stats.idi_tag, softc->rx_stats.idi_map,
	    BUS_DMASYNC_PREREAD);

/* 
 * Additional 512 bytes for future expansion.
 * To prevent corruption when loaded with newer firmwares with added counters.
 * This can be deleted when there will be no further additions of counters.
 */
#define BNXT_PORT_STAT_PADDING  512

	rc = iflib_dma_alloc(ctx, sizeof(struct rx_port_stats) + BNXT_PORT_STAT_PADDING,
	    &softc->hw_rx_port_stats, 0);
	if (rc)
		goto hw_port_rx_stats_alloc_fail;

	bus_dmamap_sync(softc->hw_rx_port_stats.idi_tag, 
            softc->hw_rx_port_stats.idi_map, BUS_DMASYNC_PREREAD);

	rc = iflib_dma_alloc(ctx, sizeof(struct tx_port_stats) + BNXT_PORT_STAT_PADDING,
	    &softc->hw_tx_port_stats, 0);

	if (rc)
		goto hw_port_tx_stats_alloc_fail;

	bus_dmamap_sync(softc->hw_tx_port_stats.idi_tag, 
            softc->hw_tx_port_stats.idi_map, BUS_DMASYNC_PREREAD);

	softc->rx_port_stats = (void *) softc->hw_rx_port_stats.idi_vaddr;
	softc->tx_port_stats = (void *) softc->hw_tx_port_stats.idi_vaddr;

	for (i = 0; i < nrxqsets; i++) {
		/* Allocation the completion ring */
		softc->rx_cp_rings[i].stats_ctx_id = HWRM_NA_SIGNATURE;
		softc->rx_cp_rings[i].ring.phys_id =
		    (uint16_t)HWRM_NA_SIGNATURE;
		softc->rx_cp_rings[i].ring.softc = softc;
		softc->rx_cp_rings[i].ring.id = i + 1;
		softc->rx_cp_rings[i].ring.doorbell =
		    softc->rx_cp_rings[i].ring.id * 0x80;
		/*
		 * If this ring overflows, RX stops working.
		 */
		softc->rx_cp_rings[i].ring.ring_size =
		    softc->scctx->isc_nrxd[0];
		softc->rx_cp_rings[i].ring.vaddr = vaddrs[i * nrxqs];
		softc->rx_cp_rings[i].ring.paddr = paddrs[i * nrxqs];

		/* Allocate the RX ring */
		softc->rx_rings[i].phys_id = (uint16_t)HWRM_NA_SIGNATURE;
		softc->rx_rings[i].softc = softc;
		softc->rx_rings[i].id = i + 1;
		softc->rx_rings[i].doorbell = softc->rx_rings[i].id * 0x80;
		softc->rx_rings[i].ring_size = softc->scctx->isc_nrxd[1];
		softc->rx_rings[i].vaddr = vaddrs[i * nrxqs + 1];
		softc->rx_rings[i].paddr = paddrs[i * nrxqs + 1];

		/* Allocate the TPA start buffer */
		softc->rx_rings[i].tpa_start = malloc(sizeof(struct bnxt_full_tpa_start) *
	    		(RX_TPA_START_CMPL_AGG_ID_MASK >> RX_TPA_START_CMPL_AGG_ID_SFT),
	    		M_DEVBUF, M_NOWAIT | M_ZERO);
		if (softc->rx_rings[i].tpa_start == NULL) {
			rc = -ENOMEM;
			device_printf(softc->dev,
					"Unable to allocate space for TPA\n");
			goto tpa_alloc_fail;
		}

		/* Allocate the AG ring */
		softc->ag_rings[i].phys_id = (uint16_t)HWRM_NA_SIGNATURE;
		softc->ag_rings[i].softc = softc;
		softc->ag_rings[i].id = nrxqsets + i + 1;
		softc->ag_rings[i].doorbell = softc->ag_rings[i].id * 0x80;
		softc->ag_rings[i].ring_size = softc->scctx->isc_nrxd[2];
		softc->ag_rings[i].vaddr = vaddrs[i * nrxqs + 2];
		softc->ag_rings[i].paddr = paddrs[i * nrxqs + 2];

		/* Allocate the ring group */
		softc->grp_info[i].grp_id = (uint16_t)HWRM_NA_SIGNATURE;
		softc->grp_info[i].stats_ctx =
		    softc->rx_cp_rings[i].stats_ctx_id;
		softc->grp_info[i].rx_ring_id = softc->rx_rings[i].phys_id;
		softc->grp_info[i].ag_ring_id = softc->ag_rings[i].phys_id;
		softc->grp_info[i].cp_ring_id =
		    softc->rx_cp_rings[i].ring.phys_id;

		bnxt_create_rx_sysctls(softc, i);
	}

	/*
	 * When SR-IOV is enabled, avoid each VF sending PORT_QSTATS
         * HWRM every sec with which firmware timeouts can happen
         */
	if (BNXT_PF(softc))
        	bnxt_create_port_stats_sysctls(softc);

	/* And finally, the VNIC */
	softc->vnic_info.id = (uint16_t)HWRM_NA_SIGNATURE;
	softc->vnic_info.flow_id = (uint16_t)HWRM_NA_SIGNATURE;
	softc->vnic_info.filter_id = -1;
	softc->vnic_info.def_ring_grp = (uint16_t)HWRM_NA_SIGNATURE;
	softc->vnic_info.cos_rule = (uint16_t)HWRM_NA_SIGNATURE;
	softc->vnic_info.lb_rule = (uint16_t)HWRM_NA_SIGNATURE;
	softc->vnic_info.rx_mask = HWRM_CFA_L2_SET_RX_MASK_INPUT_MASK_BCAST;
	softc->vnic_info.mc_list_count = 0;
	softc->vnic_info.flags = BNXT_VNIC_FLAG_DEFAULT;
	rc = iflib_dma_alloc(ctx, BNXT_MAX_MC_ADDRS * ETHER_ADDR_LEN,
	    &softc->vnic_info.mc_list, 0);
	if (rc)
		goto mc_list_alloc_fail;

	/* The VNIC RSS Hash Key */
	rc = iflib_dma_alloc(ctx, HW_HASH_KEY_SIZE,
	    &softc->vnic_info.rss_hash_key_tbl, 0);
	if (rc)
		goto rss_hash_alloc_fail;
	bus_dmamap_sync(softc->vnic_info.rss_hash_key_tbl.idi_tag,
	    softc->vnic_info.rss_hash_key_tbl.idi_map,
	    BUS_DMASYNC_PREWRITE);
	memcpy(softc->vnic_info.rss_hash_key_tbl.idi_vaddr,
	    softc->vnic_info.rss_hash_key, HW_HASH_KEY_SIZE);

	/* Allocate the RSS tables */
	rc = iflib_dma_alloc(ctx, HW_HASH_INDEX_SIZE * sizeof(uint16_t),
	    &softc->vnic_info.rss_grp_tbl, 0);
	if (rc)
		goto rss_grp_alloc_fail;
	bus_dmamap_sync(softc->vnic_info.rss_grp_tbl.idi_tag,
	    softc->vnic_info.rss_grp_tbl.idi_map,
	    BUS_DMASYNC_PREWRITE);
	memset(softc->vnic_info.rss_grp_tbl.idi_vaddr, 0xff,
	    softc->vnic_info.rss_grp_tbl.idi_size);

	softc->nrxqsets = nrxqsets;
	return rc;

rss_grp_alloc_fail:
	iflib_dma_free(&softc->vnic_info.rss_hash_key_tbl);
rss_hash_alloc_fail:
	iflib_dma_free(&softc->vnic_info.mc_list);
tpa_alloc_fail:
mc_list_alloc_fail:
	for (i = i - 1; i >= 0; i--)
		free(softc->rx_rings[i].tpa_start, M_DEVBUF);
	iflib_dma_free(&softc->hw_tx_port_stats);
hw_port_tx_stats_alloc_fail:
	iflib_dma_free(&softc->hw_rx_port_stats);
hw_port_rx_stats_alloc_fail:
	iflib_dma_free(&softc->rx_stats);
hw_stats_alloc_fail:
	free(softc->grp_info, M_DEVBUF);
grp_alloc_fail:
	free(softc->ag_rings, M_DEVBUF);
ag_alloc_fail:
	free(softc->rx_rings, M_DEVBUF);
ring_alloc_fail:
	free(softc->rx_cp_rings, M_DEVBUF);
cp_alloc_fail:
	return rc;
}