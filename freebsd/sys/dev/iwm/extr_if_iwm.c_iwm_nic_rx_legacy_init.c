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
struct TYPE_6__ {int paddr; } ;
struct TYPE_5__ {int paddr; } ;
struct TYPE_7__ {TYPE_2__ stat_dma; TYPE_1__ free_desc_dma; } ;
struct iwm_softc {TYPE_4__* cfg; TYPE_3__ rxq; } ;
struct TYPE_8__ {scalar_t__ host_interrupt_operation_mode; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IWM_CSR_INT_COALESCING ; 
 int /*<<< orphan*/  IWM_FH_MEM_RCSR_CHNL0_CONFIG_REG ; 
 int /*<<< orphan*/  IWM_FH_MEM_RCSR_CHNL0_FLUSH_RB_REQ ; 
 int /*<<< orphan*/  IWM_FH_MEM_RCSR_CHNL0_RBDCB_WPTR ; 
 int IWM_FH_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_INT_HOST_VAL ; 
 int IWM_FH_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY ; 
 int IWM_FH_RCSR_RX_CONFIG_CHNL_EN_ENABLE_VAL ; 
 int IWM_FH_RCSR_RX_CONFIG_RBDCB_SIZE_POS ; 
 int IWM_FH_RCSR_RX_CONFIG_REG_IRQ_RBTH_POS ; 
 int IWM_FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K ; 
 int /*<<< orphan*/  IWM_FH_RSCSR_CHNL0_RBDCB_BASE_REG ; 
 int /*<<< orphan*/  IWM_FH_RSCSR_CHNL0_RBDCB_WPTR_REG ; 
 int /*<<< orphan*/  IWM_FH_RSCSR_CHNL0_RDPTR ; 
 int /*<<< orphan*/  IWM_FH_RSCSR_CHNL0_STTS_WPTR_REG ; 
 int /*<<< orphan*/  IWM_FH_RSCSR_CHNL0_WPTR ; 
 int /*<<< orphan*/  IWM_HOST_INT_OPER_MODE ; 
 int /*<<< orphan*/  IWM_HOST_INT_TIMEOUT_DEF ; 
 int IWM_RX_QUEUE_SIZE_LOG ; 
 int IWM_RX_RB_TIMEOUT ; 
 int /*<<< orphan*/  IWM_SETBITS (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWM_WRITE_1 (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_nic_lock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_nic_unlock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_pcie_rx_stop (struct iwm_softc*) ; 

__attribute__((used)) static int
iwm_nic_rx_legacy_init(struct iwm_softc *sc)
{

	/* Stop Rx DMA */
	iwm_pcie_rx_stop(sc);

	if (!iwm_nic_lock(sc))
		return EBUSY;

	/* reset and flush pointers */
	IWM_WRITE(sc, IWM_FH_MEM_RCSR_CHNL0_RBDCB_WPTR, 0);
	IWM_WRITE(sc, IWM_FH_MEM_RCSR_CHNL0_FLUSH_RB_REQ, 0);
	IWM_WRITE(sc, IWM_FH_RSCSR_CHNL0_RDPTR, 0);
	IWM_WRITE(sc, IWM_FH_RSCSR_CHNL0_RBDCB_WPTR_REG, 0);

	/* Set physical address of RX ring (256-byte aligned). */
	IWM_WRITE(sc,
	    IWM_FH_RSCSR_CHNL0_RBDCB_BASE_REG,
	    sc->rxq.free_desc_dma.paddr >> 8);

	/* Set physical address of RX status (16-byte aligned). */
	IWM_WRITE(sc,
	    IWM_FH_RSCSR_CHNL0_STTS_WPTR_REG, sc->rxq.stat_dma.paddr >> 4);

	/* Enable Rx DMA
	 * XXX 5000 HW isn't supported by the iwm(4) driver.
	 * IWM_FH_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY is set because of HW bug in
	 *      the credit mechanism in 5000 HW RX FIFO
	 * Direct rx interrupts to hosts
	 * Rx buffer size 4 or 8k or 12k
	 * RB timeout 0x10
	 * 256 RBDs
	 */
	IWM_WRITE(sc, IWM_FH_MEM_RCSR_CHNL0_CONFIG_REG,
	    IWM_FH_RCSR_RX_CONFIG_CHNL_EN_ENABLE_VAL		|
	    IWM_FH_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY		|  /* HW bug */
	    IWM_FH_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_INT_HOST_VAL	|
	    IWM_FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K		|
	    (IWM_RX_RB_TIMEOUT << IWM_FH_RCSR_RX_CONFIG_REG_IRQ_RBTH_POS) |
	    IWM_RX_QUEUE_SIZE_LOG << IWM_FH_RCSR_RX_CONFIG_RBDCB_SIZE_POS);

	IWM_WRITE_1(sc, IWM_CSR_INT_COALESCING, IWM_HOST_INT_TIMEOUT_DEF);

	/* W/A for interrupt coalescing bug in 7260 and 3160 */
	if (sc->cfg->host_interrupt_operation_mode)
		IWM_SETBITS(sc, IWM_CSR_INT_COALESCING, IWM_HOST_INT_OPER_MODE);

	iwm_nic_unlock(sc);

	IWM_WRITE(sc, IWM_FH_RSCSR_CHNL0_WPTR, 8);

	return 0;
}