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
struct bge_softc {int bge_asf_mode; scalar_t__ bge_link; int /*<<< orphan*/  bge_ifp; int /*<<< orphan*/  bge_tx_saved_considx; int /*<<< orphan*/  bge_stat_ch; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int ASF_STACKUP ; 
 int /*<<< orphan*/  BGE_BMANMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_BMAN_MODE ; 
 int /*<<< orphan*/  BGE_CLRBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_DMACMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_DMAC_MODE ; 
 int /*<<< orphan*/  BGE_FTQ_RESET ; 
 int /*<<< orphan*/  BGE_HCCMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_HCC_MODE ; 
 scalar_t__ BGE_IS_5700_FAMILY (struct bge_softc*) ; 
 scalar_t__ BGE_IS_5705_PLUS (struct bge_softc*) ; 
 scalar_t__ BGE_IS_JUMBO_CAPABLE (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_MARBMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_MARB_MODE ; 
 int /*<<< orphan*/  BGE_MBCFMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_MBCF_MODE ; 
 int /*<<< orphan*/  BGE_MBX_IRQ0_LO ; 
 int /*<<< orphan*/  BGE_MODECTL_STACKUP ; 
 int /*<<< orphan*/  BGE_MODE_CTL ; 
 int /*<<< orphan*/  BGE_PCIMISCCTL_MASK_PCI_INTR ; 
 int /*<<< orphan*/  BGE_PCI_MISC_CTL ; 
 int /*<<< orphan*/  BGE_RBDCMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RBDC_MODE ; 
 int /*<<< orphan*/  BGE_RBDIMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RBDI_MODE ; 
 int /*<<< orphan*/  BGE_RDBDI_MODE ; 
 int /*<<< orphan*/  BGE_RDCMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RDC_MODE ; 
 int /*<<< orphan*/  BGE_RDMAMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RDMA_MODE ; 
 int /*<<< orphan*/  BGE_RESET_SHUTDOWN ; 
 int /*<<< orphan*/  BGE_RXLPMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RXLP_MODE ; 
 int /*<<< orphan*/  BGE_RXLSMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RXLS_MODE ; 
 int /*<<< orphan*/  BGE_RXMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_RX_MODE ; 
 int /*<<< orphan*/  BGE_SBDCMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_SBDC_MODE ; 
 int /*<<< orphan*/  BGE_SBDIMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_SBDI_MODE ; 
 int /*<<< orphan*/  BGE_SDCMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_SDC_MODE ; 
 int /*<<< orphan*/  BGE_SDIMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_SDI_MODE ; 
 int /*<<< orphan*/  BGE_SETBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_SRSMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_SRS_MODE ; 
 int /*<<< orphan*/  BGE_TXCONS_UNSET ; 
 int /*<<< orphan*/  BGE_WDMAMODE_ENABLE ; 
 int /*<<< orphan*/  BGE_WDMA_MODE ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bge_free_rx_ring_jumbo (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_free_rx_ring_std (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_free_tx_ring (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_reset (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_sig_legacy (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_sig_post_reset (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_sig_pre_reset (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_stats_update_regs (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_stop_block (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_stop_fw (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bge_stop(struct bge_softc *sc)
{
	if_t ifp;

	BGE_LOCK_ASSERT(sc);

	ifp = sc->bge_ifp;

	callout_stop(&sc->bge_stat_ch);

	/* Disable host interrupts. */
	BGE_SETBIT(sc, BGE_PCI_MISC_CTL, BGE_PCIMISCCTL_MASK_PCI_INTR);
	bge_writembx(sc, BGE_MBX_IRQ0_LO, 1);

	/*
	 * Tell firmware we're shutting down.
	 */
	bge_stop_fw(sc);
	bge_sig_pre_reset(sc, BGE_RESET_SHUTDOWN);

	/*
	 * Disable all of the receiver blocks.
	 */
	bge_stop_block(sc, BGE_RX_MODE, BGE_RXMODE_ENABLE);
	bge_stop_block(sc, BGE_RBDI_MODE, BGE_RBDIMODE_ENABLE);
	bge_stop_block(sc, BGE_RXLP_MODE, BGE_RXLPMODE_ENABLE);
	if (BGE_IS_5700_FAMILY(sc))
		bge_stop_block(sc, BGE_RXLS_MODE, BGE_RXLSMODE_ENABLE);
	bge_stop_block(sc, BGE_RDBDI_MODE, BGE_RBDIMODE_ENABLE);
	bge_stop_block(sc, BGE_RDC_MODE, BGE_RDCMODE_ENABLE);
	bge_stop_block(sc, BGE_RBDC_MODE, BGE_RBDCMODE_ENABLE);

	/*
	 * Disable all of the transmit blocks.
	 */
	bge_stop_block(sc, BGE_SRS_MODE, BGE_SRSMODE_ENABLE);
	bge_stop_block(sc, BGE_SBDI_MODE, BGE_SBDIMODE_ENABLE);
	bge_stop_block(sc, BGE_SDI_MODE, BGE_SDIMODE_ENABLE);
	bge_stop_block(sc, BGE_RDMA_MODE, BGE_RDMAMODE_ENABLE);
	bge_stop_block(sc, BGE_SDC_MODE, BGE_SDCMODE_ENABLE);
	if (BGE_IS_5700_FAMILY(sc))
		bge_stop_block(sc, BGE_DMAC_MODE, BGE_DMACMODE_ENABLE);
	bge_stop_block(sc, BGE_SBDC_MODE, BGE_SBDCMODE_ENABLE);

	/*
	 * Shut down all of the memory managers and related
	 * state machines.
	 */
	bge_stop_block(sc, BGE_HCC_MODE, BGE_HCCMODE_ENABLE);
	bge_stop_block(sc, BGE_WDMA_MODE, BGE_WDMAMODE_ENABLE);
	if (BGE_IS_5700_FAMILY(sc))
		bge_stop_block(sc, BGE_MBCF_MODE, BGE_MBCFMODE_ENABLE);

	CSR_WRITE_4(sc, BGE_FTQ_RESET, 0xFFFFFFFF);
	CSR_WRITE_4(sc, BGE_FTQ_RESET, 0);
	if (!(BGE_IS_5705_PLUS(sc))) {
		BGE_CLRBIT(sc, BGE_BMAN_MODE, BGE_BMANMODE_ENABLE);
		BGE_CLRBIT(sc, BGE_MARB_MODE, BGE_MARBMODE_ENABLE);
	}
	/* Update MAC statistics. */
	if (BGE_IS_5705_PLUS(sc))
		bge_stats_update_regs(sc);

	bge_reset(sc);
	bge_sig_legacy(sc, BGE_RESET_SHUTDOWN);
	bge_sig_post_reset(sc, BGE_RESET_SHUTDOWN);

	/*
	 * Keep the ASF firmware running if up.
	 */
	if (sc->bge_asf_mode & ASF_STACKUP)
		BGE_SETBIT(sc, BGE_MODE_CTL, BGE_MODECTL_STACKUP);
	else
		BGE_CLRBIT(sc, BGE_MODE_CTL, BGE_MODECTL_STACKUP);

	/* Free the RX lists. */
	bge_free_rx_ring_std(sc);

	/* Free jumbo RX list. */
	if (BGE_IS_JUMBO_CAPABLE(sc))
		bge_free_rx_ring_jumbo(sc);

	/* Free TX buffers. */
	bge_free_tx_ring(sc);

	sc->bge_tx_saved_considx = BGE_TXCONS_UNSET;

	/* Clear MAC's link state (PHY may still have link UP). */
	if (bootverbose && sc->bge_link)
		if_printf(sc->bge_ifp, "link DOWN\n");
	sc->bge_link = 0;

	if_setdrvflagbits(ifp, 0, (IFF_DRV_RUNNING | IFF_DRV_OACTIVE));
}