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
typedef  int uint32_t ;
struct ti_softc {scalar_t__ ti_hwrev; int ti_hdrsplit; int /*<<< orphan*/  ti_dev; TYPE_1__* ti_ifp; int /*<<< orphan*/  ti_linkstat; } ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ti_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int PCIM_CMD_MWIEN ; 
 int /*<<< orphan*/  TI_CLRBIT (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 int TI_CPUSTATE_HALT ; 
 int TI_CPUSTATE_ROMFAIL ; 
 int /*<<< orphan*/  TI_CPU_CTL_B ; 
 int /*<<< orphan*/  TI_CPU_STATE ; 
 int TI_DMA_STATE_THRESH_8W ; 
 int /*<<< orphan*/  TI_EV_CODE_LINK_DOWN ; 
 int /*<<< orphan*/  TI_GCR_DMA_READCFG ; 
 int /*<<< orphan*/  TI_GCR_DMA_WRITECFG ; 
 int /*<<< orphan*/  TI_GCR_OPMODE ; 
 scalar_t__ TI_HWREV_TIGON ; 
 scalar_t__ TI_HWREV_TIGON_II ; 
 int TI_MCR_SRAM_SYNCHRONOUS ; 
 int TI_MHC_BIGENDIAN_INIT ; 
 int TI_MHC_CHIP_REV_MASK ; 
 int TI_MHC_LITTLEENDIAN_INIT ; 
 int /*<<< orphan*/  TI_MISC_CONF ; 
 int /*<<< orphan*/  TI_MISC_HOST_CTL ; 
 int /*<<< orphan*/  TI_MISC_LOCAL_CTL ; 
 int TI_MLC_SRAM_BANK_512K ; 
 int TI_OPMODE_1_DMA_ACTIVE ; 
 int TI_OPMODE_BYTESWAP_BD ; 
 int TI_OPMODE_BYTESWAP_DATA ; 
 int TI_OPMODE_DONT_FRAG_JUMBO ; 
 int TI_OPMODE_FATAL_ENB ; 
 int TI_OPMODE_JUMBO_HDRSPLIT ; 
 int TI_OPMODE_WARN_ENB ; 
 int TI_OPMODE_WORDSWAP_BD ; 
 int TI_PCISTATE_MINDMA ; 
 int TI_PCISTATE_READ_MAXDMA ; 
 int TI_PCISTATE_USE_MEM_RD_MULT ; 
 int TI_PCISTATE_WRITE_MAXDMA ; 
 int /*<<< orphan*/  TI_PCI_BIST ; 
 int /*<<< orphan*/  TI_PCI_CMDSTAT ; 
 int TI_PCI_READ_CMD ; 
 int /*<<< orphan*/  TI_PCI_STATE ; 
 int TI_PCI_WRITE_CMD ; 
#define  TI_REV_TIGON_I 129 
#define  TI_REV_TIGON_II 128 
 int /*<<< orphan*/  TI_SETBIT (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ti_64bitslot_war (struct ti_softc*) ; 

__attribute__((used)) static int
ti_chipinit(struct ti_softc *sc)
{
	uint32_t cacheline;
	uint32_t pci_writemax = 0;
	uint32_t hdrsplit;

	/* Initialize link to down state. */
	sc->ti_linkstat = TI_EV_CODE_LINK_DOWN;

	/* Set endianness before we access any non-PCI registers. */
#if 0 && BYTE_ORDER == BIG_ENDIAN
	CSR_WRITE_4(sc, TI_MISC_HOST_CTL,
	    TI_MHC_BIGENDIAN_INIT | (TI_MHC_BIGENDIAN_INIT << 24));
#else
	CSR_WRITE_4(sc, TI_MISC_HOST_CTL,
	    TI_MHC_LITTLEENDIAN_INIT | (TI_MHC_LITTLEENDIAN_INIT << 24));
#endif

	/* Check the ROM failed bit to see if self-tests passed. */
	if (CSR_READ_4(sc, TI_CPU_STATE) & TI_CPUSTATE_ROMFAIL) {
		device_printf(sc->ti_dev, "board self-diagnostics failed!\n");
		return (ENODEV);
	}

	/* Halt the CPU. */
	TI_SETBIT(sc, TI_CPU_STATE, TI_CPUSTATE_HALT);

	/* Figure out the hardware revision. */
	switch (CSR_READ_4(sc, TI_MISC_HOST_CTL) & TI_MHC_CHIP_REV_MASK) {
	case TI_REV_TIGON_I:
		sc->ti_hwrev = TI_HWREV_TIGON;
		break;
	case TI_REV_TIGON_II:
		sc->ti_hwrev = TI_HWREV_TIGON_II;
		break;
	default:
		device_printf(sc->ti_dev, "unsupported chip revision\n");
		return (ENODEV);
	}

	/* Do special setup for Tigon 2. */
	if (sc->ti_hwrev == TI_HWREV_TIGON_II) {
		TI_SETBIT(sc, TI_CPU_CTL_B, TI_CPUSTATE_HALT);
		TI_SETBIT(sc, TI_MISC_LOCAL_CTL, TI_MLC_SRAM_BANK_512K);
		TI_SETBIT(sc, TI_MISC_CONF, TI_MCR_SRAM_SYNCHRONOUS);
	}

	/*
	 * We don't have firmware source for the Tigon 1, so Tigon 1 boards
	 * can't do header splitting.
	 */
#ifdef TI_JUMBO_HDRSPLIT
	if (sc->ti_hwrev != TI_HWREV_TIGON)
		sc->ti_hdrsplit = 1;
	else
		device_printf(sc->ti_dev,
		    "can't do header splitting on a Tigon I board\n");
#endif /* TI_JUMBO_HDRSPLIT */

	/* Set up the PCI state register. */
	CSR_WRITE_4(sc, TI_PCI_STATE, TI_PCI_READ_CMD|TI_PCI_WRITE_CMD);
	if (sc->ti_hwrev == TI_HWREV_TIGON_II) {
		TI_SETBIT(sc, TI_PCI_STATE, TI_PCISTATE_USE_MEM_RD_MULT);
	}

	/* Clear the read/write max DMA parameters. */
	TI_CLRBIT(sc, TI_PCI_STATE, (TI_PCISTATE_WRITE_MAXDMA|
	    TI_PCISTATE_READ_MAXDMA));

	/* Get cache line size. */
	cacheline = CSR_READ_4(sc, TI_PCI_BIST) & 0xFF;

	/*
	 * If the system has set enabled the PCI memory write
	 * and invalidate command in the command register, set
	 * the write max parameter accordingly. This is necessary
	 * to use MWI with the Tigon 2.
	 */
	if (CSR_READ_4(sc, TI_PCI_CMDSTAT) & PCIM_CMD_MWIEN) {
		switch (cacheline) {
		case 1:
		case 4:
		case 8:
		case 16:
		case 32:
		case 64:
			break;
		default:
		/* Disable PCI memory write and invalidate. */
			if (bootverbose)
				device_printf(sc->ti_dev, "cache line size %d"
				    " not supported; disabling PCI MWI\n",
				    cacheline);
			CSR_WRITE_4(sc, TI_PCI_CMDSTAT, CSR_READ_4(sc,
			    TI_PCI_CMDSTAT) & ~PCIM_CMD_MWIEN);
			break;
		}
	}

	TI_SETBIT(sc, TI_PCI_STATE, pci_writemax);

	/* This sets the min dma param all the way up (0xff). */
	TI_SETBIT(sc, TI_PCI_STATE, TI_PCISTATE_MINDMA);

	if (sc->ti_hdrsplit)
		hdrsplit = TI_OPMODE_JUMBO_HDRSPLIT;
	else
		hdrsplit = 0;

	/* Configure DMA variables. */
#if BYTE_ORDER == BIG_ENDIAN
	CSR_WRITE_4(sc, TI_GCR_OPMODE, TI_OPMODE_BYTESWAP_BD |
	    TI_OPMODE_BYTESWAP_DATA | TI_OPMODE_WORDSWAP_BD |
	    TI_OPMODE_WARN_ENB | TI_OPMODE_FATAL_ENB |
	    TI_OPMODE_DONT_FRAG_JUMBO | hdrsplit);
#else /* BYTE_ORDER */
	CSR_WRITE_4(sc, TI_GCR_OPMODE, TI_OPMODE_BYTESWAP_DATA|
	    TI_OPMODE_WORDSWAP_BD|TI_OPMODE_DONT_FRAG_JUMBO|
	    TI_OPMODE_WARN_ENB|TI_OPMODE_FATAL_ENB | hdrsplit);
#endif /* BYTE_ORDER */

	/*
	 * Only allow 1 DMA channel to be active at a time.
	 * I don't think this is a good idea, but without it
	 * the firmware racks up lots of nicDmaReadRingFull
	 * errors.  This is not compatible with hardware checksums.
	 */
	if ((sc->ti_ifp->if_capenable & (IFCAP_TXCSUM | IFCAP_RXCSUM)) == 0)
		TI_SETBIT(sc, TI_GCR_OPMODE, TI_OPMODE_1_DMA_ACTIVE);

	/* Recommended settings from Tigon manual. */
	CSR_WRITE_4(sc, TI_GCR_DMA_WRITECFG, TI_DMA_STATE_THRESH_8W);
	CSR_WRITE_4(sc, TI_GCR_DMA_READCFG, TI_DMA_STATE_THRESH_8W);

	if (ti_64bitslot_war(sc)) {
		device_printf(sc->ti_dev, "bios thinks we're in a 64 bit slot, "
		    "but we aren't");
		return (EINVAL);
	}

	return (0);
}