#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_6__ {int hc_rate; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int hc_rate; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  flags; } ;
struct ecore_queue_init_params {size_t max_cos; int /*<<< orphan*/ ** cxts; TYPE_2__ tx; TYPE_1__ rx; } ;
struct bxe_softc {int hc_rx_ticks; int hc_tx_ticks; size_t max_cos; TYPE_4__* context; } ;
struct bxe_fastpath {int index; int /*<<< orphan*/  fw_sb_id; } ;
struct TYPE_8__ {TYPE_3__* vcxt; } ;
struct TYPE_7__ {int /*<<< orphan*/  eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,size_t) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  ECORE_Q_FLG_HC ; 
 int /*<<< orphan*/  ECORE_Q_FLG_HC_EN ; 
 size_t FIRST_TX_COS_INDEX ; 
 int /*<<< orphan*/  HC_INDEX_ETH_FIRST_TX_CQ_CONS ; 
 int /*<<< orphan*/  HC_INDEX_ETH_RX_CQ_CONS ; 
 int ILT_PAGE_CIDS ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_pf_q_prep_init(struct bxe_softc               *sc,
                   struct bxe_fastpath            *fp,
                   struct ecore_queue_init_params *init_params)
{
    uint8_t cos;
    int cxt_index, cxt_offset;

    bxe_set_bit(ECORE_Q_FLG_HC, &init_params->rx.flags);
    bxe_set_bit(ECORE_Q_FLG_HC, &init_params->tx.flags);

    bxe_set_bit(ECORE_Q_FLG_HC_EN, &init_params->rx.flags);
    bxe_set_bit(ECORE_Q_FLG_HC_EN, &init_params->tx.flags);

    /* HC rate */
    init_params->rx.hc_rate =
        sc->hc_rx_ticks ? (1000000 / sc->hc_rx_ticks) : 0;
    init_params->tx.hc_rate =
        sc->hc_tx_ticks ? (1000000 / sc->hc_tx_ticks) : 0;

    /* FW SB ID */
    init_params->rx.fw_sb_id = init_params->tx.fw_sb_id = fp->fw_sb_id;

    /* CQ index among the SB indices */
    init_params->rx.sb_cq_index = HC_INDEX_ETH_RX_CQ_CONS;
    init_params->tx.sb_cq_index = HC_INDEX_ETH_FIRST_TX_CQ_CONS;

    /* set maximum number of COSs supported by this queue */
    init_params->max_cos = sc->max_cos;

    BLOGD(sc, DBG_LOAD, "fp %d setting queue params max cos to %d\n",
          fp->index, init_params->max_cos);

    /* set the context pointers queue object */
    for (cos = FIRST_TX_COS_INDEX; cos < init_params->max_cos; cos++) {
        /* XXX change index/cid here if ever support multiple tx CoS */
        /* fp->txdata[cos]->cid */
        cxt_index = fp->index / ILT_PAGE_CIDS;
        cxt_offset = fp->index - (cxt_index * ILT_PAGE_CIDS);
        init_params->cxts[cos] = &sc->context[cxt_index].vcxt[cxt_offset].eth;
    }
}