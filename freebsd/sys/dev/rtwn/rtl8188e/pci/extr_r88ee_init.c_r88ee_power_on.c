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
struct rtwn_softc {scalar_t__ sc_hwcrypto; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ R88E_XCK_OUT_CTRL ; 
 int R88E_XCK_OUT_CTRL_EN ; 
 scalar_t__ R92C_AFE_XTAL_CTRL ; 
 scalar_t__ R92C_AFE_XTAL_CTRL_EXT ; 
 scalar_t__ R92C_APS_FSMCO ; 
 int R92C_APS_FSMCO_AFSM_HSUS ; 
 int R92C_APS_FSMCO_AFSM_PCIE ; 
 int R92C_APS_FSMCO_APDM_HPDN ; 
 int R92C_APS_FSMCO_APFM_ONMAC ; 
 int R92C_APS_FSMCO_PDN_EN ; 
 int R92C_APS_FSMCO_SUS_HOST ; 
 scalar_t__ R92C_CR ; 
 int R92C_CR_CALTMR_EN ; 
 int R92C_CR_ENSEC ; 
 int R92C_CR_HCI_RXDMA_EN ; 
 int R92C_CR_HCI_TXDMA_EN ; 
 int R92C_CR_PROTOCOL_EN ; 
 int R92C_CR_RXDMA_EN ; 
 int R92C_CR_SCHEDULE_EN ; 
 int R92C_CR_TXDMA_EN ; 
 scalar_t__ R92C_GPIO_MUXCFG ; 
 int R92C_GPIO_MUXCFG_ENSIC ; 
 int /*<<< orphan*/  R92C_INT_MIG ; 
 scalar_t__ R92C_LPLDO_CTRL ; 
 int R92C_LPLDO_CTRL_SLEEP ; 
 int /*<<< orphan*/  R92C_MCUTST_1 ; 
 scalar_t__ R92C_PCIE_CTRL_REG ; 
 int /*<<< orphan*/  R92C_RSV_CTRL ; 
 scalar_t__ R92C_SYS_CLKR ; 
 scalar_t__ R92C_SYS_FUNC_EN ; 
 int R92C_SYS_FUNC_EN_BBRSTB ; 
 int R92C_SYS_FUNC_EN_BB_GLB_RST ; 
 scalar_t__ RTWN_CRYPTO_SW ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int rtwn_read_2 (struct rtwn_softc*,scalar_t__) ; 
 int rtwn_read_4 (struct rtwn_softc*,scalar_t__) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1_shift (struct rtwn_softc*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  rtwn_setbits_2 (struct rtwn_softc*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_2 (struct rtwn_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
r88ee_power_on(struct rtwn_softc *sc)
{
	int ntries;

	/* Disable XTAL output for power saving. */
	rtwn_setbits_1(sc, R88E_XCK_OUT_CTRL, R88E_XCK_OUT_CTRL_EN, 0);

	/* Unlock ISO/CLK/Power control register. */
	rtwn_setbits_2(sc, R92C_APS_FSMCO, R92C_APS_FSMCO_APDM_HPDN, 0);
	rtwn_write_1(sc, R92C_RSV_CTRL, 0);

	/* Wait for power ready bit */
	for(ntries = 0; ntries < 5000; ntries++) {
		if (rtwn_read_4(sc, R92C_APS_FSMCO) & R92C_APS_FSMCO_SUS_HOST)
			break;
		rtwn_delay(sc, 10);
	}
	if (ntries == 5000) {
		device_printf(sc->sc_dev,
		    "timeout waiting for chip power up\n");
		return (ETIMEDOUT);
	}

	/* Reset BB. */
	rtwn_setbits_1(sc, R92C_SYS_FUNC_EN,
	    R92C_SYS_FUNC_EN_BBRSTB | R92C_SYS_FUNC_EN_BB_GLB_RST, 0);

	/* schmit trigger */
	rtwn_setbits_1(sc, R92C_AFE_XTAL_CTRL + 2, 0, 0x80);

	/* Disable HWPDN. */
	rtwn_setbits_1_shift(sc, R92C_APS_FSMCO,
	    R92C_APS_FSMCO_APDM_HPDN, 0, 1);

	/* Disable WL suspend. */
	rtwn_setbits_1_shift(sc, R92C_APS_FSMCO,
	    R92C_APS_FSMCO_AFSM_HSUS | R92C_APS_FSMCO_AFSM_PCIE, 0, 1);

	/* Auto-enable WLAN */
	rtwn_setbits_1_shift(sc, R92C_APS_FSMCO,
	    0, R92C_APS_FSMCO_APFM_ONMAC, 1);
	for (ntries = 0; ntries < 5000; ntries++) {
		if (!(rtwn_read_2(sc, R92C_APS_FSMCO) &
		    R92C_APS_FSMCO_APFM_ONMAC))
			break;
		rtwn_delay(sc, 10);
	}
	if (ntries == 5000)
		return (ETIMEDOUT);

	rtwn_setbits_1(sc, R92C_PCIE_CTRL_REG + 2, 0, 0x04);

	/* Enable LDO normal mode. */
	rtwn_setbits_1(sc, R92C_LPLDO_CTRL, R92C_LPLDO_CTRL_SLEEP, 0);

	rtwn_setbits_1(sc, R92C_APS_FSMCO, 0, R92C_APS_FSMCO_PDN_EN);
	rtwn_setbits_1(sc, R92C_PCIE_CTRL_REG + 2, 0, 0x04);
	rtwn_setbits_1(sc, R92C_AFE_XTAL_CTRL_EXT + 1, 0, 0x02);
	rtwn_setbits_1(sc, R92C_SYS_CLKR, 0, 0x08);
	rtwn_setbits_2(sc, R92C_GPIO_MUXCFG, R92C_GPIO_MUXCFG_ENSIC, 0);

	/* Enable MAC DMA/WMAC/SCHEDULE/SEC blocks. */
	rtwn_write_2(sc, R92C_CR, 0);
	rtwn_setbits_2(sc, R92C_CR, 0,
	    R92C_CR_HCI_TXDMA_EN | R92C_CR_TXDMA_EN |
	    R92C_CR_HCI_RXDMA_EN | R92C_CR_RXDMA_EN |
	    R92C_CR_PROTOCOL_EN | R92C_CR_SCHEDULE_EN |
	    ((sc->sc_hwcrypto != RTWN_CRYPTO_SW) ? R92C_CR_ENSEC : 0) |
	    R92C_CR_CALTMR_EN);

	rtwn_write_4(sc, R92C_INT_MIG, 0);
	rtwn_write_4(sc, R92C_MCUTST_1, 0);

	return (0);
}