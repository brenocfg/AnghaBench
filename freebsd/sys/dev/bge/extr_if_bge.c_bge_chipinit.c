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
typedef  int uint16_t ;
struct bge_softc {int bge_flags; scalar_t__ bge_chiprev; scalar_t__ bge_asicrev; int bge_mps; scalar_t__ bge_chipid; int bge_asf_mode; int /*<<< orphan*/  bge_dev; } ;

/* Variables and functions */
 int ASF_STACKUP ; 
 int BGE_32BITTIME_66MHZ ; 
 scalar_t__ BGE_ASICREV_BCM5700 ; 
 scalar_t__ BGE_ASICREV_BCM5701 ; 
 scalar_t__ BGE_ASICREV_BCM5703 ; 
 scalar_t__ BGE_ASICREV_BCM5704 ; 
 scalar_t__ BGE_ASICREV_BCM5705 ; 
 scalar_t__ BGE_ASICREV_BCM5717 ; 
 scalar_t__ BGE_ASICREV_BCM5720 ; 
 scalar_t__ BGE_ASICREV_BCM5750 ; 
 scalar_t__ BGE_ASICREV_BCM5762 ; 
 scalar_t__ BGE_ASICREV_BCM57765 ; 
 scalar_t__ BGE_ASICREV_BCM57766 ; 
 scalar_t__ BGE_ASICREV_BCM5780 ; 
 scalar_t__ BGE_ASICREV_BCM5906 ; 
 scalar_t__ BGE_CHIPID_BCM5701_B5 ; 
 scalar_t__ BGE_CHIPID_BCM57765_A0 ; 
 scalar_t__ BGE_CHIPREV_5704_BX ; 
 scalar_t__ BGE_CHIPREV_57765_AX ; 
 int /*<<< orphan*/  BGE_CLRBIT (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_CPMU_PADRNG_CTL ; 
 int BGE_CPMU_PADRNG_CTL_RDIV2 ; 
 int BGE_FLAG_PCIE ; 
 int BGE_FLAG_PCIX ; 
 int BGE_FLAG_TAGGED_STATUS ; 
 int BGE_INIT ; 
 scalar_t__ BGE_IS_5714_FAMILY (struct bge_softc*) ; 
 scalar_t__ BGE_IS_5717_PLUS (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_IS_57765_PLUS (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_MEMWIN_WRITE (struct bge_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_MISCCFG_EPHY_IDDQ ; 
 int /*<<< orphan*/  BGE_MISC_CFG ; 
 int BGE_MODECTL_B2HRX_ENABLE ; 
 int BGE_MODECTL_BYTESWAP_B2HRX_DATA ; 
 int BGE_MODECTL_FORCE_PCI32 ; 
 int BGE_MODECTL_HOST_SEND_BDS ; 
 int BGE_MODECTL_HTX2B_ENABLE ; 
 int BGE_MODECTL_MAC_ATTN_INTR ; 
 int BGE_MODECTL_STACKUP ; 
 int BGE_MODECTL_TX_NO_PHDR_CSUM ; 
 int BGE_MODECTL_WORDSWAP_B2HRX_DATA ; 
 int /*<<< orphan*/  BGE_MODE_CTL ; 
 int BGE_PCIDMARWCTL_ASRT_ALL_BE ; 
 int BGE_PCIDMARWCTL_CRDRDR_RDMA_MRRS_MSK ; 
 int BGE_PCIDMARWCTL_DIS_CACHE_ALIGNMENT ; 
 int BGE_PCIDMARWCTL_MINDMA ; 
 int BGE_PCIDMARWCTL_ONEDMA_ATONCE_GLOBAL ; 
 int BGE_PCIDMARWCTL_ONEDMA_ATONCE_LOCAL ; 
 int BGE_PCIDMARWCTL_RD_CMD_SHIFT (int) ; 
 int BGE_PCIDMARWCTL_RD_WAT_SHIFT (int) ; 
 int BGE_PCIDMARWCTL_TAGGED_STATUS_WA ; 
 int BGE_PCIDMARWCTL_USE_MRM ; 
 int BGE_PCIDMARWCTL_WR_CMD_SHIFT (int) ; 
 int BGE_PCIDMARWCTL_WR_WAT_SHIFT (int) ; 
 int BGE_PCIMISCCTL_TAGGED_STATUS ; 
 int /*<<< orphan*/  BGE_PCI_CLKCTL ; 
 int /*<<< orphan*/  BGE_PCI_CMD ; 
 scalar_t__ BGE_PCI_DMA_RW_CTL ; 
 scalar_t__ BGE_PCI_MISC_CTL ; 
 scalar_t__ BGE_PCI_MSI_DATA ; 
 int BGE_STATS_BLOCK ; 
 int BGE_STATS_BLOCK_END ; 
 int BGE_STATUS_BLOCK ; 
 int BGE_STATUS_BLOCK_END ; 
 int CSR_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PCIM_CMD_MWIEN ; 
 int /*<<< orphan*/  PCI_CLRBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bge_dma_swap_options (struct bge_softc*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
bge_chipinit(struct bge_softc *sc)
{
	uint32_t dma_rw_ctl, misc_ctl, mode_ctl;
	uint16_t val;
	int i;

	/* Set endianness before we access any non-PCI registers. */
	misc_ctl = BGE_INIT;
	if (sc->bge_flags & BGE_FLAG_TAGGED_STATUS)
		misc_ctl |= BGE_PCIMISCCTL_TAGGED_STATUS;
	pci_write_config(sc->bge_dev, BGE_PCI_MISC_CTL, misc_ctl, 4);

	/*
	 * Clear the MAC statistics block in the NIC's
	 * internal memory.
	 */
	for (i = BGE_STATS_BLOCK;
	    i < BGE_STATS_BLOCK_END + 1; i += sizeof(uint32_t))
		BGE_MEMWIN_WRITE(sc, i, 0);

	for (i = BGE_STATUS_BLOCK;
	    i < BGE_STATUS_BLOCK_END + 1; i += sizeof(uint32_t))
		BGE_MEMWIN_WRITE(sc, i, 0);

	if (sc->bge_chiprev == BGE_CHIPREV_5704_BX) {
		/*
		 *  Fix data corruption caused by non-qword write with WB.
		 *  Fix master abort in PCI mode.
		 *  Fix PCI latency timer.
		 */
		val = pci_read_config(sc->bge_dev, BGE_PCI_MSI_DATA + 2, 2);
		val |= (1 << 10) | (1 << 12) | (1 << 13);
		pci_write_config(sc->bge_dev, BGE_PCI_MSI_DATA + 2, val, 2);
	}

	if (sc->bge_asicrev == BGE_ASICREV_BCM57765 ||
	    sc->bge_asicrev == BGE_ASICREV_BCM57766) {
		/*
		 * For the 57766 and non Ax versions of 57765, bootcode
		 * needs to setup the PCIE Fast Training Sequence (FTS)
		 * value to prevent transmit hangs.
		 */
		if (sc->bge_chiprev != BGE_CHIPREV_57765_AX) {
			CSR_WRITE_4(sc, BGE_CPMU_PADRNG_CTL,
			    CSR_READ_4(sc, BGE_CPMU_PADRNG_CTL) |
			    BGE_CPMU_PADRNG_CTL_RDIV2);
		}
	}

	/*
	 * Set up the PCI DMA control register.
	 */
	dma_rw_ctl = BGE_PCIDMARWCTL_RD_CMD_SHIFT(6) |
	    BGE_PCIDMARWCTL_WR_CMD_SHIFT(7);
	if (sc->bge_flags & BGE_FLAG_PCIE) {
		if (sc->bge_mps >= 256)
			dma_rw_ctl |= BGE_PCIDMARWCTL_WR_WAT_SHIFT(7);
		else
			dma_rw_ctl |= BGE_PCIDMARWCTL_WR_WAT_SHIFT(3);
	} else if (sc->bge_flags & BGE_FLAG_PCIX) {
		if (BGE_IS_5714_FAMILY(sc)) {
			/* 256 bytes for read and write. */
			dma_rw_ctl |= BGE_PCIDMARWCTL_RD_WAT_SHIFT(2) |
			    BGE_PCIDMARWCTL_WR_WAT_SHIFT(2);
			dma_rw_ctl |= (sc->bge_asicrev == BGE_ASICREV_BCM5780) ?
			    BGE_PCIDMARWCTL_ONEDMA_ATONCE_GLOBAL :
			    BGE_PCIDMARWCTL_ONEDMA_ATONCE_LOCAL;
		} else if (sc->bge_asicrev == BGE_ASICREV_BCM5703) {
			/*
			 * In the BCM5703, the DMA read watermark should
			 * be set to less than or equal to the maximum
			 * memory read byte count of the PCI-X command
			 * register.
			 */
			dma_rw_ctl |= BGE_PCIDMARWCTL_RD_WAT_SHIFT(4) |
			    BGE_PCIDMARWCTL_WR_WAT_SHIFT(3);
		} else if (sc->bge_asicrev == BGE_ASICREV_BCM5704) {
			/* 1536 bytes for read, 384 bytes for write. */
			dma_rw_ctl |= BGE_PCIDMARWCTL_RD_WAT_SHIFT(7) |
			    BGE_PCIDMARWCTL_WR_WAT_SHIFT(3);
		} else {
			/* 384 bytes for read and write. */
			dma_rw_ctl |= BGE_PCIDMARWCTL_RD_WAT_SHIFT(3) |
			    BGE_PCIDMARWCTL_WR_WAT_SHIFT(3) |
			    0x0F;
		}
		if (sc->bge_asicrev == BGE_ASICREV_BCM5703 ||
		    sc->bge_asicrev == BGE_ASICREV_BCM5704) {
			uint32_t tmp;

			/* Set ONE_DMA_AT_ONCE for hardware workaround. */
			tmp = CSR_READ_4(sc, BGE_PCI_CLKCTL) & 0x1F;
			if (tmp == 6 || tmp == 7)
				dma_rw_ctl |=
				    BGE_PCIDMARWCTL_ONEDMA_ATONCE_GLOBAL;

			/* Set PCI-X DMA write workaround. */
			dma_rw_ctl |= BGE_PCIDMARWCTL_ASRT_ALL_BE;
		}
	} else {
		/* Conventional PCI bus: 256 bytes for read and write. */
		dma_rw_ctl |= BGE_PCIDMARWCTL_RD_WAT_SHIFT(7) |
		    BGE_PCIDMARWCTL_WR_WAT_SHIFT(7);

		if (sc->bge_asicrev != BGE_ASICREV_BCM5705 &&
		    sc->bge_asicrev != BGE_ASICREV_BCM5750)
			dma_rw_ctl |= 0x0F;
	}
	if (sc->bge_asicrev == BGE_ASICREV_BCM5700 ||
	    sc->bge_asicrev == BGE_ASICREV_BCM5701)
		dma_rw_ctl |= BGE_PCIDMARWCTL_USE_MRM |
		    BGE_PCIDMARWCTL_ASRT_ALL_BE;
	if (sc->bge_asicrev == BGE_ASICREV_BCM5703 ||
	    sc->bge_asicrev == BGE_ASICREV_BCM5704)
		dma_rw_ctl &= ~BGE_PCIDMARWCTL_MINDMA;
	if (BGE_IS_5717_PLUS(sc)) {
		dma_rw_ctl &= ~BGE_PCIDMARWCTL_DIS_CACHE_ALIGNMENT;
		if (sc->bge_chipid == BGE_CHIPID_BCM57765_A0)
			dma_rw_ctl &= ~BGE_PCIDMARWCTL_CRDRDR_RDMA_MRRS_MSK;
		/*
		 * Enable HW workaround for controllers that misinterpret
		 * a status tag update and leave interrupts permanently
		 * disabled.
		 */
		if (!BGE_IS_57765_PLUS(sc) &&
		    sc->bge_asicrev != BGE_ASICREV_BCM5717 &&
		    sc->bge_asicrev != BGE_ASICREV_BCM5762)
			dma_rw_ctl |= BGE_PCIDMARWCTL_TAGGED_STATUS_WA;
	}
	pci_write_config(sc->bge_dev, BGE_PCI_DMA_RW_CTL, dma_rw_ctl, 4);

	/*
	 * Set up general mode register.
	 */
	mode_ctl = bge_dma_swap_options(sc);
	if (sc->bge_asicrev == BGE_ASICREV_BCM5720 ||
	    sc->bge_asicrev == BGE_ASICREV_BCM5762) {
		/* Retain Host-2-BMC settings written by APE firmware. */
		mode_ctl |= CSR_READ_4(sc, BGE_MODE_CTL) &
		    (BGE_MODECTL_BYTESWAP_B2HRX_DATA |
		    BGE_MODECTL_WORDSWAP_B2HRX_DATA |
		    BGE_MODECTL_B2HRX_ENABLE | BGE_MODECTL_HTX2B_ENABLE);
	}
	mode_ctl |= BGE_MODECTL_MAC_ATTN_INTR | BGE_MODECTL_HOST_SEND_BDS |
	    BGE_MODECTL_TX_NO_PHDR_CSUM;

	/*
	 * BCM5701 B5 have a bug causing data corruption when using
	 * 64-bit DMA reads, which can be terminated early and then
	 * completed later as 32-bit accesses, in combination with
	 * certain bridges.
	 */
	if (sc->bge_asicrev == BGE_ASICREV_BCM5701 &&
	    sc->bge_chipid == BGE_CHIPID_BCM5701_B5)
		mode_ctl |= BGE_MODECTL_FORCE_PCI32;

	/*
	 * Tell the firmware the driver is running
	 */
	if (sc->bge_asf_mode & ASF_STACKUP)
		mode_ctl |= BGE_MODECTL_STACKUP;

	CSR_WRITE_4(sc, BGE_MODE_CTL, mode_ctl);

	/*
	 * Disable memory write invalidate.  Apparently it is not supported
	 * properly by these devices.
	 */
	PCI_CLRBIT(sc->bge_dev, BGE_PCI_CMD, PCIM_CMD_MWIEN, 4);

	/* Set the timer prescaler (always 66 MHz). */
	CSR_WRITE_4(sc, BGE_MISC_CFG, BGE_32BITTIME_66MHZ);

	/* XXX: The Linux tg3 driver does this at the start of brgphy_reset. */
	if (sc->bge_asicrev == BGE_ASICREV_BCM5906) {
		DELAY(40);	/* XXX */

		/* Put PHY into ready state */
		BGE_CLRBIT(sc, BGE_MISC_CFG, BGE_MISCCFG_EPHY_IDDQ);
		CSR_READ_4(sc, BGE_MISC_CFG); /* Flush */
		DELAY(40);
	}

	return (0);
}