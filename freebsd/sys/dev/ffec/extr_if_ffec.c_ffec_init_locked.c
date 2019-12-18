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
typedef  int uint32_t ;
struct ifnet {int if_drv_flags; } ;
struct ffec_softc {int rxdesc_ring_paddr; int txdesc_ring_paddr; int fecflags; int /*<<< orphan*/  ffec_callout; int /*<<< orphan*/  mii_softc; scalar_t__ txcount; scalar_t__ tx_idx_tail; scalar_t__ tx_idx_head; scalar_t__ rx_idx; int /*<<< orphan*/  rxbuf_align; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int FECFLAG_RACC ; 
 int FEC_ECR_DBSWP ; 
 int FEC_ECR_ETHEREN ; 
 int /*<<< orphan*/  FEC_ECR_REG ; 
 int /*<<< orphan*/  FEC_FTRL_REG ; 
 int /*<<< orphan*/  FEC_IEM_REG ; 
 int FEC_IER_EBERR ; 
 int /*<<< orphan*/  FEC_IER_REG ; 
 int FEC_IER_RXF ; 
 int FEC_IER_TXF ; 
 int FEC_MIBC_DIS ; 
 int /*<<< orphan*/  FEC_MIBC_REG ; 
 int /*<<< orphan*/  FEC_MRBR_REG ; 
 int FEC_MRBR_R_BUF_SIZE_SHIFT ; 
 int /*<<< orphan*/  FEC_OPD_REG ; 
 int /*<<< orphan*/  FEC_RACC_REG ; 
 int FEC_RACC_SHIFT16 ; 
 int FEC_RCR_MAX_FL_SHIFT ; 
 int /*<<< orphan*/  FEC_RCR_REG ; 
 int FEC_RDAR_RDAR ; 
 int /*<<< orphan*/  FEC_RDAR_REG ; 
 int /*<<< orphan*/  FEC_RDSR_REG ; 
 int /*<<< orphan*/  FEC_TCR_REG ; 
 int /*<<< orphan*/  FEC_TDSR_REG ; 
 int /*<<< orphan*/  FEC_TFWR_REG ; 
 int FEC_TFWR_STRFWD ; 
 int FEC_TFWR_TWFR_128BYTE ; 
 int /*<<< orphan*/  FFEC_ASSERT_LOCKED (struct ffec_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int MCLBYTES ; 
 int RD4 (struct ffec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct ffec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_clear_stats (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_setup_rxfilter (struct ffec_softc*) ; 
 int /*<<< orphan*/  ffec_tick ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ffec_init_locked(struct ffec_softc *sc)
{
	struct ifnet *ifp = sc->ifp;
	uint32_t maxbuf, maxfl, regval;

	FFEC_ASSERT_LOCKED(sc);

	/*
	 * The hardware has a limit of 0x7ff as the max frame length (see
	 * comments for MRBR below), and we use mbuf clusters as receive
	 * buffers, and we currently are designed to receive an entire frame
	 * into a single buffer.
	 *
	 * We start with a MCLBYTES-sized cluster, but we have to offset into
	 * the buffer by ETHER_ALIGN to make room for post-receive re-alignment,
	 * and then that value has to be rounded up to the hardware's DMA
	 * alignment requirements, so all in all our buffer is that much smaller
	 * than MCLBYTES.
	 *
	 * The resulting value is used as the frame truncation length and the
	 * max buffer receive buffer size for now.  It'll become more complex
	 * when we support jumbo frames and receiving fragments of them into
	 * separate buffers.
	 */
	maxbuf = MCLBYTES - roundup(ETHER_ALIGN, sc->rxbuf_align);
	maxfl = min(maxbuf, 0x7ff);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	/* Mask all interrupts and clear all current interrupt status bits. */
	WR4(sc, FEC_IEM_REG, 0x00000000);
	WR4(sc, FEC_IER_REG, 0xffffffff);

	/*
	 * Go set up palr/puar, galr/gaur, ialr/iaur.
	 */
	ffec_setup_rxfilter(sc);

	/*
	 * TFWR - Transmit FIFO watermark register.
	 *
	 * Set the transmit fifo watermark register to "store and forward" mode
	 * and also set a threshold of 128 bytes in the fifo before transmission
	 * of a frame begins (to avoid dma underruns).  Recent FEC hardware
	 * supports STRFWD and when that bit is set, the watermark level in the
	 * low bits is ignored.  Older hardware doesn't have STRFWD, but writing
	 * to that bit is innocuous, and the TWFR bits get used instead.
	 */
	WR4(sc, FEC_TFWR_REG, FEC_TFWR_STRFWD | FEC_TFWR_TWFR_128BYTE);

	/* RCR - Receive control register.
	 *
	 * Set max frame length + clean out anything left from u-boot.
	 */
	WR4(sc, FEC_RCR_REG, (maxfl << FEC_RCR_MAX_FL_SHIFT));

	/*
	 * TCR - Transmit control register.
	 *
	 * Clean out anything left from u-boot.  Any necessary values are set in
	 * ffec_miibus_statchg() based on the media type.
	 */
	WR4(sc, FEC_TCR_REG, 0);
        
	/*
	 * OPD - Opcode/pause duration.
	 *
	 * XXX These magic numbers come from u-boot.
	 */
	WR4(sc, FEC_OPD_REG, 0x00010020);

	/*
	 * FRSR - Fifo receive start register.
	 *
	 * This register does not exist on imx6, it is present on earlier
	 * hardware. The u-boot code sets this to a non-default value that's 32
	 * bytes larger than the default, with no clue as to why.  The default
	 * value should work fine, so there's no code to init it here.
	 */

	/*
	 *  MRBR - Max RX buffer size.
	 *
	 *  Note: For hardware prior to imx6 this value cannot exceed 0x07ff,
	 *  but the datasheet says no such thing for imx6.  On the imx6, setting
	 *  this to 2K without setting EN1588 resulted in a crazy runaway
	 *  receive loop in the hardware, where every rx descriptor in the ring
	 *  had its EMPTY flag cleared, no completion or error flags set, and a
	 *  length of zero.  I think maybe you can only exceed it when EN1588 is
	 *  set, like maybe that's what enables jumbo frames, because in general
	 *  the EN1588 flag seems to be the "enable new stuff" vs. "be legacy-
	 *  compatible" flag.
	 */
	WR4(sc, FEC_MRBR_REG, maxfl << FEC_MRBR_R_BUF_SIZE_SHIFT);

	/*
	 * FTRL - Frame truncation length.
	 *
	 * Must be greater than or equal to the value set in FEC_RCR_MAXFL.
	 */
	WR4(sc, FEC_FTRL_REG, maxfl);

	/*
	 * RDSR / TDSR descriptor ring pointers.
	 *
	 * When we turn on ECR_ETHEREN at the end, the hardware zeroes its
	 * internal current descriptor index values for both rings, so we zero
	 * our index values as well.
	 */
	sc->rx_idx = 0;
	sc->tx_idx_head = sc->tx_idx_tail = 0;
	sc->txcount = 0;
	WR4(sc, FEC_RDSR_REG, sc->rxdesc_ring_paddr);
	WR4(sc, FEC_TDSR_REG, sc->txdesc_ring_paddr);

	/*
	 * EIM - interrupt mask register.
	 *
	 * We always enable the same set of interrupts while running; unlike
	 * some drivers there's no need to change the mask on the fly depending
	 * on what operations are in progress.
	 */
	WR4(sc, FEC_IEM_REG, FEC_IER_TXF | FEC_IER_RXF | FEC_IER_EBERR);

	/*
	 * MIBC - MIB control (hardware stats); clear all statistics regs, then
	 * enable collection of statistics.
	 */
	regval = RD4(sc, FEC_MIBC_REG);
	WR4(sc, FEC_MIBC_REG, regval | FEC_MIBC_DIS);
	ffec_clear_stats(sc);
	WR4(sc, FEC_MIBC_REG, regval & ~FEC_MIBC_DIS);

	if (sc->fecflags & FECFLAG_RACC) {
		/*
		 * RACC - Receive Accelerator Function Configuration.
		 */
		regval = RD4(sc, FEC_RACC_REG);
		WR4(sc, FEC_RACC_REG, regval | FEC_RACC_SHIFT16);
	}

	/*
	 * ECR - Ethernet control register.
	 *
	 * This must happen after all the other config registers are set.  If
	 * we're running on little-endian hardware, also set the flag for byte-
	 * swapping descriptor ring entries.  This flag doesn't exist on older
	 * hardware, but it can be safely set -- the bit position it occupies
	 * was unused.
	 */
	regval = RD4(sc, FEC_ECR_REG);
#if _BYTE_ORDER == _LITTLE_ENDIAN
	regval |= FEC_ECR_DBSWP;
#endif
	regval |= FEC_ECR_ETHEREN;
	WR4(sc, FEC_ECR_REG, regval);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

       /*
	* Call mii_mediachg() which will call back into ffec_miibus_statchg() to
	* set up the remaining config registers based on the current media.
	*/
	mii_mediachg(sc->mii_softc);
	callout_reset(&sc->ffec_callout, hz, ffec_tick, sc);

	/*
	 * Tell the hardware that receive buffers are available.  They were made
	 * available in ffec_attach() or ffec_stop().
	 */
	WR4(sc, FEC_RDAR_REG, FEC_RDAR_RDAR);
}