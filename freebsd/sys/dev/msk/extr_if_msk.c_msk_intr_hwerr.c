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
struct msk_softc {int msk_intrhwemask; int /*<<< orphan*/ ** msk_if; int /*<<< orphan*/  msk_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_HWE_IMSK ; 
 int /*<<< orphan*/  B0_HWE_ISRC ; 
 int /*<<< orphan*/  B2_TST_CTRL1 ; 
 int CSR_PCI_READ_4 (struct msk_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_PCI_WRITE_4 (struct msk_softc*,scalar_t__,int) ; 
 int CSR_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GMAC_TI_ST_CTRL ; 
 int /*<<< orphan*/  GMT_ST_CLR_IRQ ; 
 size_t MSK_PORT_A ; 
 size_t MSK_PORT_B ; 
 int PCIM_STATUS_MDPERR ; 
 int PCIM_STATUS_PERR ; 
 int PCIM_STATUS_RMABORT ; 
 int PCIM_STATUS_RTABORT ; 
 int PCIM_STATUS_SERR ; 
 int /*<<< orphan*/  PCIR_STATUS ; 
 int PEX_FATAL_ERRORS ; 
 scalar_t__ PEX_HEADER_LOG ; 
 int PEX_POIS_TLP ; 
 scalar_t__ PEX_UNC_ERR_STAT ; 
 int PEX_UNSUP_REQ ; 
 int /*<<< orphan*/  TST_CFG_WRITE_OFF ; 
 int /*<<< orphan*/  TST_CFG_WRITE_ON ; 
 int Y2_HWE_L1_MASK ; 
 int Y2_HWE_L2_MASK ; 
 int Y2_IS_IRQ_STAT ; 
 int Y2_IS_MST_ERR ; 
 int Y2_IS_PCI_EXP ; 
 int Y2_IS_PCI_NEXP ; 
 int Y2_IS_TIST_OV ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msk_handle_hwerr (int /*<<< orphan*/ *,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
msk_intr_hwerr(struct msk_softc *sc)
{
	uint32_t status;
	uint32_t tlphead[4];

	status = CSR_READ_4(sc, B0_HWE_ISRC);
	/* Time Stamp timer overflow. */
	if ((status & Y2_IS_TIST_OV) != 0)
		CSR_WRITE_1(sc, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);
	if ((status & Y2_IS_PCI_NEXP) != 0) {
		/*
		 * PCI Express Error occurred which is not described in PEX
		 * spec.
		 * This error is also mapped either to Master Abort(
		 * Y2_IS_MST_ERR) or Target Abort (Y2_IS_IRQ_STAT) bit and
		 * can only be cleared there.
                 */
		device_printf(sc->msk_dev,
		    "PCI Express protocol violation error\n");
	}

	if ((status & (Y2_IS_MST_ERR | Y2_IS_IRQ_STAT)) != 0) {
		uint16_t v16;

		if ((status & Y2_IS_MST_ERR) != 0)
			device_printf(sc->msk_dev,
			    "unexpected IRQ Status error\n");
		else
			device_printf(sc->msk_dev,
			    "unexpected IRQ Master error\n");
		/* Reset all bits in the PCI status register. */
		v16 = pci_read_config(sc->msk_dev, PCIR_STATUS, 2);
		CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_write_config(sc->msk_dev, PCIR_STATUS, v16 |
		    PCIM_STATUS_PERR | PCIM_STATUS_SERR | PCIM_STATUS_RMABORT |
		    PCIM_STATUS_RTABORT | PCIM_STATUS_MDPERR, 2);
		CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	}

	/* Check for PCI Express Uncorrectable Error. */
	if ((status & Y2_IS_PCI_EXP) != 0) {
		uint32_t v32;

		/*
		 * On PCI Express bus bridges are called root complexes (RC).
		 * PCI Express errors are recognized by the root complex too,
		 * which requests the system to handle the problem. After
		 * error occurrence it may be that no access to the adapter
		 * may be performed any longer.
		 */

		v32 = CSR_PCI_READ_4(sc, PEX_UNC_ERR_STAT);
		if ((v32 & PEX_UNSUP_REQ) != 0) {
			/* Ignore unsupported request error. */
			device_printf(sc->msk_dev,
			    "Uncorrectable PCI Express error\n");
		}
		if ((v32 & (PEX_FATAL_ERRORS | PEX_POIS_TLP)) != 0) {
			int i;

			/* Get TLP header form Log Registers. */
			for (i = 0; i < 4; i++)
				tlphead[i] = CSR_PCI_READ_4(sc,
				    PEX_HEADER_LOG + i * 4);
			/* Check for vendor defined broadcast message. */
			if (!(tlphead[0] == 0x73004001 && tlphead[1] == 0x7f)) {
				sc->msk_intrhwemask &= ~Y2_IS_PCI_EXP;
				CSR_WRITE_4(sc, B0_HWE_IMSK,
				    sc->msk_intrhwemask);
				CSR_READ_4(sc, B0_HWE_IMSK);
			}
		}
		/* Clear the interrupt. */
		CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		CSR_PCI_WRITE_4(sc, PEX_UNC_ERR_STAT, 0xffffffff);
		CSR_WRITE_1(sc, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	}

	if ((status & Y2_HWE_L1_MASK) != 0 && sc->msk_if[MSK_PORT_A] != NULL)
		msk_handle_hwerr(sc->msk_if[MSK_PORT_A], status);
	if ((status & Y2_HWE_L2_MASK) != 0 && sc->msk_if[MSK_PORT_B] != NULL)
		msk_handle_hwerr(sc->msk_if[MSK_PORT_B], status >> 8);
}