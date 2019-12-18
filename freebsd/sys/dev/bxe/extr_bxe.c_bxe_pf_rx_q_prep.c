#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint16_t ;
struct rxq_pause_params {int sge_th_hi; scalar_t__ bd_th_hi; int rcq_th_hi; int pri_map; int /*<<< orphan*/  rcq_th_lo; int /*<<< orphan*/  bd_th_lo; int /*<<< orphan*/  sge_th_lo; } ;
struct ecore_rxq_setup_params {int max_sges_pkt; int /*<<< orphan*/  silent_removal_mask; int /*<<< orphan*/  silent_removal_value; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  cache_line_log; int /*<<< orphan*/  max_tpa_queues; void* mcast_engine_id; void* rss_engine_id; void* sge_buf_sz; void* tpa_agg_sz; int /*<<< orphan*/  cl_qzone_id; scalar_t__ buf_sz; scalar_t__ rcq_np_map; scalar_t__ rcq_map; int /*<<< orphan*/  sge_map; int /*<<< orphan*/  dscr_map; } ;
struct TYPE_9__ {int /*<<< orphan*/  afex_def_vlan_tag; } ;
struct TYPE_10__ {TYPE_4__ mf_info; } ;
struct bxe_softc {int mtu; void* max_aggregation_size; scalar_t__ rx_ring_size; TYPE_5__ devinfo; scalar_t__ dropless_fc; } ;
struct TYPE_8__ {scalar_t__ paddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  paddr; } ;
struct bxe_fastpath {int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  cl_qzone_id; scalar_t__ rx_buf_size; TYPE_3__ rcq_dma; TYPE_2__ rx_sge_dma; TYPE_1__ rx_dma; } ;

/* Variables and functions */
 scalar_t__ BCM_PAGE_SIZE ; 
 scalar_t__ BD_TH_HI (struct bxe_softc*) ; 
 int /*<<< orphan*/  BD_TH_LO (struct bxe_softc*) ; 
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_RX_ALIGN_SHIFT ; 
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  EVL_VLID_MASK ; 
 int FW_PREFETCH_CNT ; 
 int /*<<< orphan*/  HC_INDEX_ETH_RX_CQ_CONS ; 
 scalar_t__ IP_HEADER_ALIGNMENT_PADDING ; 
 scalar_t__ IS_MF_AFEX (struct bxe_softc*) ; 
 int /*<<< orphan*/  MAX_AGG_QS (struct bxe_softc*) ; 
 int PAGES_PER_SGE ; 
 int PAGES_PER_SGE_SHIFT ; 
 int RCQ_NUM_PAGES ; 
 int RCQ_TH_HI (struct bxe_softc*) ; 
 int /*<<< orphan*/  RCQ_TH_LO (struct bxe_softc*) ; 
 int RCQ_USABLE_PER_PAGE ; 
 int RX_SGE_NUM_PAGES ; 
 int RX_SGE_USABLE_PER_PAGE ; 
 void* SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  SGE_PAGES ; 
 int SGE_PAGE_ALIGN (int) ; 
 int SGE_PAGE_SHIFT ; 
 int SGE_TH_HI (struct bxe_softc*) ; 
 int /*<<< orphan*/  SGE_TH_LO (struct bxe_softc*) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_pf_rx_q_prep(struct bxe_softc              *sc,
                 struct bxe_fastpath           *fp,
                 struct rxq_pause_params       *pause,
                 struct ecore_rxq_setup_params *rxq_init)
{
    uint8_t max_sge = 0;
    uint16_t sge_sz = 0;
    uint16_t tpa_agg_size = 0;

    pause->sge_th_lo = SGE_TH_LO(sc);
    pause->sge_th_hi = SGE_TH_HI(sc);

    /* validate SGE ring has enough to cross high threshold */
    if (sc->dropless_fc &&
            (pause->sge_th_hi + FW_PREFETCH_CNT) >
            (RX_SGE_USABLE_PER_PAGE * RX_SGE_NUM_PAGES)) {
        BLOGW(sc, "sge ring threshold limit\n");
    }

    /* minimum max_aggregation_size is 2*MTU (two full buffers) */
    tpa_agg_size = (2 * sc->mtu);
    if (tpa_agg_size < sc->max_aggregation_size) {
        tpa_agg_size = sc->max_aggregation_size;
    }

    max_sge = SGE_PAGE_ALIGN(sc->mtu) >> SGE_PAGE_SHIFT;
    max_sge = ((max_sge + PAGES_PER_SGE - 1) &
                   (~(PAGES_PER_SGE - 1))) >> PAGES_PER_SGE_SHIFT;
    sge_sz = (uint16_t)min(SGE_PAGES, 0xffff);

    /* pause - not for e1 */
    if (!CHIP_IS_E1(sc)) {
        pause->bd_th_lo = BD_TH_LO(sc);
        pause->bd_th_hi = BD_TH_HI(sc);

        pause->rcq_th_lo = RCQ_TH_LO(sc);
        pause->rcq_th_hi = RCQ_TH_HI(sc);

        /* validate rings have enough entries to cross high thresholds */
        if (sc->dropless_fc &&
            pause->bd_th_hi + FW_PREFETCH_CNT >
            sc->rx_ring_size) {
            BLOGW(sc, "rx bd ring threshold limit\n");
        }

        if (sc->dropless_fc &&
            pause->rcq_th_hi + FW_PREFETCH_CNT >
            RCQ_NUM_PAGES * RCQ_USABLE_PER_PAGE) {
            BLOGW(sc, "rcq ring threshold limit\n");
        }

        pause->pri_map = 1;
    }

    /* rxq setup */
    rxq_init->dscr_map   = fp->rx_dma.paddr;
    rxq_init->sge_map    = fp->rx_sge_dma.paddr;
    rxq_init->rcq_map    = fp->rcq_dma.paddr;
    rxq_init->rcq_np_map = (fp->rcq_dma.paddr + BCM_PAGE_SIZE);

    /*
     * This should be a maximum number of data bytes that may be
     * placed on the BD (not including paddings).
     */
    rxq_init->buf_sz = (fp->rx_buf_size -
                        IP_HEADER_ALIGNMENT_PADDING);

    rxq_init->cl_qzone_id     = fp->cl_qzone_id;
    rxq_init->tpa_agg_sz      = tpa_agg_size;
    rxq_init->sge_buf_sz      = sge_sz;
    rxq_init->max_sges_pkt    = max_sge;
    rxq_init->rss_engine_id   = SC_FUNC(sc);
    rxq_init->mcast_engine_id = SC_FUNC(sc);

    /*
     * Maximum number or simultaneous TPA aggregation for this Queue.
     * For PF Clients it should be the maximum available number.
     * VF driver(s) may want to define it to a smaller value.
     */
    rxq_init->max_tpa_queues = MAX_AGG_QS(sc);

    rxq_init->cache_line_log = BXE_RX_ALIGN_SHIFT;
    rxq_init->fw_sb_id = fp->fw_sb_id;

    rxq_init->sb_cq_index = HC_INDEX_ETH_RX_CQ_CONS;

    /*
     * configure silent vlan removal
     * if multi function mode is afex, then mask default vlan
     */
    if (IS_MF_AFEX(sc)) {
        rxq_init->silent_removal_value =
            sc->devinfo.mf_info.afex_def_vlan_tag;
        rxq_init->silent_removal_mask = EVL_VLID_MASK;
    }
}