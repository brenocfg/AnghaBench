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
typedef  scalar_t__ uint8_t ;
struct ecore_txq_setup_params {int /*<<< orphan*/  tss_leading_cl_id; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  traffic_type; scalar_t__ sb_cq_index; int /*<<< orphan*/  dscr_map; } ;
struct bxe_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  paddr; } ;
struct bxe_fastpath {int /*<<< orphan*/  fw_sb_id; TYPE_1__ tx_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_FP (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HC_INDEX_ETH_FIRST_TX_CQ_CONS ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_NW ; 
 int /*<<< orphan*/  cl_id ; 

__attribute__((used)) static void
bxe_pf_tx_q_prep(struct bxe_softc              *sc,
                 struct bxe_fastpath           *fp,
                 struct ecore_txq_setup_params *txq_init,
                 uint8_t                       cos)
{
    /*
     * XXX If multiple CoS is ever supported then each fastpath structure
     * will need to maintain tx producer/consumer/dma/etc values *per* CoS.
     * fp->txdata[cos]->tx_dma.paddr;
     */
    txq_init->dscr_map     = fp->tx_dma.paddr;
    txq_init->sb_cq_index  = HC_INDEX_ETH_FIRST_TX_CQ_CONS + cos;
    txq_init->traffic_type = LLFC_TRAFFIC_TYPE_NW;
    txq_init->fw_sb_id     = fp->fw_sb_id;

    /*
     * set the TSS leading client id for TX classfication to the
     * leading RSS client id
     */
    txq_init->tss_leading_cl_id = BXE_FP(sc, 0, cl_id);
}