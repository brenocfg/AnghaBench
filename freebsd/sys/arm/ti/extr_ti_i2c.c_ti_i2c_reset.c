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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ti_i2c_softc {int sc_con_reg; int sc_fifo_trsh; int /*<<< orphan*/  sc_mem_res; int /*<<< orphan*/ * sc_iicbus; } ;
struct ti_i2c_clock_config {int frequency; int psc; int scll; int sclh; int hsscll; int hssclh; } ;

/* Variables and functions */
#define  CHIP_AM335X 129 
#define  CHIP_OMAP_4 128 
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int I2C_BUF_RXTRSH_SHIFT ; 
 int I2C_BUF_TRSH_MASK ; 
 int I2C_CON_I2C_EN ; 
 int I2C_CON_MST ; 
 int I2C_CON_OPMODE_HS ; 
 int I2C_HSSCLH_SHIFT ; 
 int I2C_HSSCLL_SHIFT ; 
 int I2C_IE_AL ; 
 int I2C_IE_ARDY ; 
 int I2C_IE_NACK ; 
 int I2C_IE_RDR ; 
 int I2C_IE_RRDY ; 
 int I2C_IE_XDR ; 
 int I2C_IE_XRDY ; 
 int /*<<< orphan*/  I2C_REG_BUF ; 
 int /*<<< orphan*/  I2C_REG_CON ; 
 int /*<<< orphan*/  I2C_REG_IRQENABLE_SET ; 
 int /*<<< orphan*/  I2C_REG_PSC ; 
 int /*<<< orphan*/  I2C_REG_SCLH ; 
 int /*<<< orphan*/  I2C_REG_SCLL ; 
 int /*<<< orphan*/  I2C_REG_SYSC ; 
 int /*<<< orphan*/  I2C_REG_SYSC_SRST ; 
 int /*<<< orphan*/  I2C_REG_SYSS ; 
 int I2C_SCLH_MASK ; 
 int I2C_SCLL_MASK ; 
 int I2C_SYSS_RDONE ; 
 int IICBUS_GET_FREQUENCY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct ti_i2c_clock_config* ti_am335x_i2c_clock_configs ; 
 int ti_chip () ; 
 int ti_i2c_read_2 (struct ti_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_i2c_write_2 (struct ti_i2c_softc*,int /*<<< orphan*/ ,int) ; 
 struct ti_i2c_clock_config* ti_omap4_i2c_clock_configs ; 

__attribute__((used)) static int
ti_i2c_reset(struct ti_i2c_softc *sc, u_char speed)
{
	int timeout;
	struct ti_i2c_clock_config *clkcfg;
	u_int busfreq;
	uint16_t fifo_trsh, reg, scll, sclh;

	switch (ti_chip()) {
#ifdef SOC_OMAP4
	case CHIP_OMAP_4:
		clkcfg = ti_omap4_i2c_clock_configs;
		break;
#endif
#ifdef SOC_TI_AM335X
	case CHIP_AM335X:
		clkcfg = ti_am335x_i2c_clock_configs;
		break;
#endif
	default:
		panic("Unknown TI SoC, unable to reset the i2c");
	}

	/*
	 * If we haven't attached the bus yet, just init at the default slow
	 * speed.  This lets us get the hardware initialized enough to attach
	 * the bus which is where the real speed configuration is handled. After
	 * the bus is attached, get the configured speed from it.  Search the
	 * configuration table for the best speed we can do that doesn't exceed
	 * the requested speed.
	 */
	if (sc->sc_iicbus == NULL)
		busfreq = 100000;
	else
		busfreq = IICBUS_GET_FREQUENCY(sc->sc_iicbus, speed);
	for (;;) {
		if (clkcfg[1].frequency == 0 || clkcfg[1].frequency > busfreq)
			break;
		clkcfg++;
	}

	/*
	 * 23.1.4.3 - HS I2C Software Reset
	 *    From OMAP4 TRM at page 4068.
	 *
	 * 1. Ensure that the module is disabled.
	 */
	sc->sc_con_reg = 0;
	ti_i2c_write_2(sc, I2C_REG_CON, sc->sc_con_reg);

	/* 2. Issue a softreset to the controller. */
	bus_write_2(sc->sc_mem_res, I2C_REG_SYSC, I2C_REG_SYSC_SRST);

	/*
	 * 3. Enable the module.
	 *    The I2Ci.I2C_SYSS[0] RDONE bit is asserted only after the module
	 *    is enabled by setting the I2Ci.I2C_CON[15] I2C_EN bit to 1.
	 */
	ti_i2c_write_2(sc, I2C_REG_CON, I2C_CON_I2C_EN);

 	/* 4. Wait for the software reset to complete. */
	timeout = 0;
	while ((ti_i2c_read_2(sc, I2C_REG_SYSS) & I2C_SYSS_RDONE) == 0) {
		if (timeout++ > 100)
			return (EBUSY);
		DELAY(100);
	}

	/*
	 * Disable the I2C controller once again, now that the reset has
	 * finished.
	 */
	ti_i2c_write_2(sc, I2C_REG_CON, sc->sc_con_reg);

	/*
	 * The following sequence is taken from the OMAP4 TRM at page 4077.
	 *
	 * 1. Enable the functional and interface clocks (see Section
	 *    23.1.5.1.1.1.1).  Done at ti_i2c_activate().
	 *
	 * 2. Program the prescaler to obtain an approximately 12MHz internal
	 *    sampling clock (I2Ci_INTERNAL_CLK) by programming the
	 *    corresponding value in the I2Ci.I2C_PSC[3:0] PSC field.
	 *    This value depends on the frequency of the functional clock
	 *    (I2Ci_FCLK).  Because this frequency is 96MHz, the
	 *    I2Ci.I2C_PSC[7:0] PSC field value is 0x7.
	 */
	ti_i2c_write_2(sc, I2C_REG_PSC, clkcfg->psc);

	/*
	 * 3. Program the I2Ci.I2C_SCLL[7:0] SCLL and I2Ci.I2C_SCLH[7:0] SCLH
	 *    bit fields to obtain a bit rate of 100 Kbps, 400 Kbps or 1Mbps.
	 *    These values depend on the internal sampling clock frequency
	 *    (see Table 23-8).
	 */
	scll = clkcfg->scll & I2C_SCLL_MASK;
	sclh = clkcfg->sclh & I2C_SCLH_MASK;

	/*
	 * 4. (Optional) Program the I2Ci.I2C_SCLL[15:8] HSSCLL and
	 *    I2Ci.I2C_SCLH[15:8] HSSCLH fields to obtain a bit rate of
	 *    400K bps or 3.4M bps (for the second phase of HS mode).  These
	 *    values depend on the internal sampling clock frequency (see
	 *    Table 23-8).
	 *
	 * 5. (Optional) If a bit rate of 3.4M bps is used and the bus line
	 *    capacitance exceeds 45 pF, (see Section 18.4.8, PAD Functional
	 *    Multiplexing and Configuration).
	 */
	switch (ti_chip()) {
#ifdef SOC_OMAP4
	case CHIP_OMAP_4:
		if ((clkcfg->hsscll + clkcfg->hssclh) > 0) {
			scll |= clkcfg->hsscll << I2C_HSSCLL_SHIFT;
			sclh |= clkcfg->hssclh << I2C_HSSCLH_SHIFT;
			sc->sc_con_reg |= I2C_CON_OPMODE_HS;
		}
		break;
#endif
	}

	/* Write the selected bit rate. */
	ti_i2c_write_2(sc, I2C_REG_SCLL, scll);
	ti_i2c_write_2(sc, I2C_REG_SCLH, sclh);

	/*
	 * 6. Configure the Own Address of the I2C controller by storing it in
	 *    the I2Ci.I2C_OA0 register.  Up to four Own Addresses can be
	 *    programmed in the I2Ci.I2C_OAi registers (where i = 0, 1, 2, 3)
	 *    for each I2C controller.
	 *
	 * Note: For a 10-bit address, set the corresponding expand Own Address
	 * bit in the I2Ci.I2C_CON register.
	 *
	 * Driver currently always in single master mode so ignore this step.
	 */

	/*
	 * 7. Set the TX threshold (in transmitter mode) and the RX threshold
	 *    (in receiver mode) by setting the I2Ci.I2C_BUF[5:0]XTRSH field to
	 *    (TX threshold - 1) and the I2Ci.I2C_BUF[13:8]RTRSH field to (RX
	 *    threshold - 1), where the TX and RX thresholds are greater than
	 *    or equal to 1.
	 *
	 * The threshold is set to 5 for now.
	 */
	fifo_trsh = (sc->sc_fifo_trsh - 1) & I2C_BUF_TRSH_MASK;
	reg = fifo_trsh | (fifo_trsh << I2C_BUF_RXTRSH_SHIFT);
	ti_i2c_write_2(sc, I2C_REG_BUF, reg);

	/*
	 * 8. Take the I2C controller out of reset by setting the
	 *    I2Ci.I2C_CON[15] I2C_EN bit to 1.
	 *
	 * 23.1.5.1.1.1.2 - Initialize the I2C Controller
	 *
	 * To initialize the I2C controller, perform the following steps:
	 *
	 * 1. Configure the I2Ci.I2C_CON register:
	 *     . For master or slave mode, set the I2Ci.I2C_CON[10] MST bit
	 *       (0: slave, 1: master).
	 *     . For transmitter or receiver mode, set the I2Ci.I2C_CON[9] TRX
	 *       bit (0: receiver, 1: transmitter).
	 */

	/* Enable the I2C controller in master mode. */
	sc->sc_con_reg |= I2C_CON_I2C_EN | I2C_CON_MST;
	ti_i2c_write_2(sc, I2C_REG_CON, sc->sc_con_reg);

	/*
	 * 2. If using an interrupt to transmit/receive data, set the
	 *    corresponding bit in the I2Ci.I2C_IE register (the I2Ci.I2C_IE[4]
	 *    XRDY_IE bit for the transmit interrupt, the I2Ci.I2C_IE[3] RRDY
	 *    bit for the receive interrupt).
	 */

	/* Set the interrupts we want to be notified. */
	reg = I2C_IE_XDR |	/* Transmit draining interrupt. */
	    I2C_IE_XRDY |	/* Transmit Data Ready interrupt. */
	    I2C_IE_RDR |	/* Receive draining interrupt. */
	    I2C_IE_RRDY |	/* Receive Data Ready interrupt. */
	    I2C_IE_ARDY |	/* Register Access Ready interrupt. */
	    I2C_IE_NACK |	/* No Acknowledgment interrupt. */
	    I2C_IE_AL;		/* Arbitration lost interrupt. */

	/* Enable the interrupts. */
	ti_i2c_write_2(sc, I2C_REG_IRQENABLE_SET, reg);

	/*
	 * 3. If using DMA to receive/transmit data, set to 1 the corresponding
	 *    bit in the I2Ci.I2C_BUF register (the I2Ci.I2C_BUF[15] RDMA_EN
	 *    bit for the receive DMA channel, the I2Ci.I2C_BUF[7] XDMA_EN bit
	 *    for the transmit DMA channel).
	 *
	 * Not using DMA for now, so ignore this.
	 */

	return (0);
}