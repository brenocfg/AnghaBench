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
struct TYPE_8__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_9__ {TYPE_3__ stat_dma; TYPE_2__ used_desc_dma; TYPE_1__ free_desc_dma; } ;
struct iwm_softc {TYPE_5__* cfg; TYPE_4__ rxq; } ;
struct TYPE_10__ {scalar_t__ integrated; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IWM_CSR_INT_COALESCING ; 
 int /*<<< orphan*/  IWM_HOST_INT_TIMEOUT_DEF ; 
 int IWM_RFH_DMA_EN_ENABLE_VAL ; 
 int /*<<< orphan*/  IWM_RFH_GEN_CFG ; 
 int IWM_RFH_GEN_CFG_RB_CHUNK_SIZE_128 ; 
 int IWM_RFH_GEN_CFG_RB_CHUNK_SIZE_64 ; 
 int IWM_RFH_GEN_CFG_RFH_DMA_SNOOP ; 
 int IWM_RFH_GEN_CFG_SERVICE_DMA_SNOOP ; 
 int /*<<< orphan*/  IWM_RFH_Q0_FRBDCB_BA_LSB ; 
 int /*<<< orphan*/  IWM_RFH_Q0_FRBDCB_RIDX ; 
 int /*<<< orphan*/  IWM_RFH_Q0_FRBDCB_WIDX ; 
 int /*<<< orphan*/  IWM_RFH_Q0_FRBDCB_WIDX_TRG ; 
 int /*<<< orphan*/  IWM_RFH_Q0_URBDCB_BA_LSB ; 
 int /*<<< orphan*/  IWM_RFH_Q0_URBDCB_WIDX ; 
 int /*<<< orphan*/  IWM_RFH_Q0_URBD_STTS_WPTR_LSB ; 
 int /*<<< orphan*/  IWM_RFH_RXF_DMA_CFG ; 
 int IWM_RFH_RXF_DMA_DROP_TOO_LARGE_MASK ; 
 int IWM_RFH_RXF_DMA_MIN_RB_4_8 ; 
 int IWM_RFH_RXF_DMA_RBDCB_SIZE_512 ; 
 int IWM_RFH_RXF_DMA_RB_SIZE_4K ; 
 int /*<<< orphan*/  IWM_RFH_RXF_RXQ_ACTIVE ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWM_WRITE_1 (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_nic_lock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_nic_unlock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_write_prph (struct iwm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwm_write_prph64 (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwm_nic_rx_mq_init(struct iwm_softc *sc)
{
	int enabled;

	if (!iwm_nic_lock(sc))
		return EBUSY;

	/* Stop RX DMA. */
	iwm_write_prph(sc, IWM_RFH_RXF_DMA_CFG, 0);
	/* Disable RX used and free queue operation. */
	iwm_write_prph(sc, IWM_RFH_RXF_RXQ_ACTIVE, 0);

	iwm_write_prph64(sc, IWM_RFH_Q0_FRBDCB_BA_LSB,
	    sc->rxq.free_desc_dma.paddr);
	iwm_write_prph64(sc, IWM_RFH_Q0_URBDCB_BA_LSB,
	    sc->rxq.used_desc_dma.paddr);
	iwm_write_prph64(sc, IWM_RFH_Q0_URBD_STTS_WPTR_LSB,
	    sc->rxq.stat_dma.paddr);
	iwm_write_prph(sc, IWM_RFH_Q0_FRBDCB_WIDX, 0);
	iwm_write_prph(sc, IWM_RFH_Q0_FRBDCB_RIDX, 0);
	iwm_write_prph(sc, IWM_RFH_Q0_URBDCB_WIDX, 0);

	/* We configure only queue 0 for now. */
	enabled = ((1 << 0) << 16) | (1 << 0);

	/* Enable RX DMA, 4KB buffer size. */
	iwm_write_prph(sc, IWM_RFH_RXF_DMA_CFG,
	    IWM_RFH_DMA_EN_ENABLE_VAL |
	    IWM_RFH_RXF_DMA_RB_SIZE_4K |
	    IWM_RFH_RXF_DMA_MIN_RB_4_8 |
	    IWM_RFH_RXF_DMA_DROP_TOO_LARGE_MASK |
	    IWM_RFH_RXF_DMA_RBDCB_SIZE_512);

	/* Enable RX DMA snooping. */
	iwm_write_prph(sc, IWM_RFH_GEN_CFG,
	    IWM_RFH_GEN_CFG_RFH_DMA_SNOOP |
	    IWM_RFH_GEN_CFG_SERVICE_DMA_SNOOP |
	    (sc->cfg->integrated ? IWM_RFH_GEN_CFG_RB_CHUNK_SIZE_64 :
	    IWM_RFH_GEN_CFG_RB_CHUNK_SIZE_128));

	/* Enable the configured queue(s). */
	iwm_write_prph(sc, IWM_RFH_RXF_RXQ_ACTIVE, enabled);

	iwm_nic_unlock(sc);

	IWM_WRITE_1(sc, IWM_CSR_INT_COALESCING, IWM_HOST_INT_TIMEOUT_DEF);

	IWM_WRITE(sc, IWM_RFH_Q0_FRBDCB_WIDX_TRG, 8);

	return (0);
}