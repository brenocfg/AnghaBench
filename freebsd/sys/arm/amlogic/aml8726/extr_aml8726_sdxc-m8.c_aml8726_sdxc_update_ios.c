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
typedef  int uint32_t ;
struct mmc_ios {int bus_width; int clock; int vdd; int power_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  pol; int /*<<< orphan*/  pin; int /*<<< orphan*/ * dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  pin; int /*<<< orphan*/ * dev; } ;
struct TYPE_5__ {struct mmc_ios ios; } ;
struct aml8726_sdxc_softc {int ref_freq; int* voltages; int /*<<< orphan*/  dev; TYPE_3__ card_rst; TYPE_2__ vselect; TYPE_1__ host; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {int voltage; int freq; int rx_phase; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_SDXC_CLK2_REG ; 
 int AML_SDXC_CLK2_RX_PHASE_SHIFT ; 
 int AML_SDXC_CLK2_SD_PHASE_SHIFT ; 
 unsigned int AML_SDXC_CLK_CNTRL_CLK_DIV_MASK ; 
 unsigned int AML_SDXC_CLK_CNTRL_CLK_DIV_SHIFT ; 
 int AML_SDXC_CLK_CNTRL_CLK_MODULE_EN ; 
 int AML_SDXC_CLK_CNTRL_CLK_SEL_MASK ; 
 int AML_SDXC_CLK_CNTRL_CLK_SEL_SHIFT ; 
 int AML_SDXC_CLK_CNTRL_MEM_PWR_MASK ; 
 int AML_SDXC_CLK_CNTRL_MEM_PWR_ON ; 
 int /*<<< orphan*/  AML_SDXC_CLK_CNTRL_REG ; 
 int AML_SDXC_CLK_CNTRL_RX_CLK_EN ; 
 int AML_SDXC_CLK_CNTRL_SD_CLK_EN ; 
 int AML_SDXC_CLK_CNTRL_TX_CLK_EN ; 
 int AML_SDXC_CNTRL_BUS_WIDTH_1 ; 
 int AML_SDXC_CNTRL_BUS_WIDTH_4 ; 
 int AML_SDXC_CNTRL_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  AML_SDXC_CNTRL_REG ; 
 int AML_SDXC_CNTRL_RX_ENDIAN_SHIFT ; 
 int AML_SDXC_CNTRL_RX_PERIOD_SHIFT ; 
 int AML_SDXC_CNTRL_RX_TIMEOUT_SHIFT ; 
 int AML_SDXC_CNTRL_TX_ENDIAN_SHIFT ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PIN_OFF_FLAG (int /*<<< orphan*/ ) ; 
 int PIN_ON_FLAG (int /*<<< orphan*/ ) ; 
 TYPE_4__* aml8726_sdxc_clk_phases ; 
 int aml8726_sdxc_power_off (struct aml8726_sdxc_softc*) ; 
 int aml8726_sdxc_power_on (struct aml8726_sdxc_softc*) ; 
#define  bus_width_1 133 
#define  bus_width_4 132 
#define  bus_width_8 131 
 struct aml8726_sdxc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
#define  power_off 130 
#define  power_on 129 
#define  power_up 128 

__attribute__((used)) static int
aml8726_sdxc_update_ios(device_t bus, device_t child)
{
	struct aml8726_sdxc_softc *sc = device_get_softc(bus);
	struct mmc_ios *ios = &sc->host.ios;
	unsigned int divisor;
	int error;
	int i;
	uint32_t cctlr;
	uint32_t clk2r;
	uint32_t ctlr;
	uint32_t freq;

	ctlr = (7 << AML_SDXC_CNTRL_TX_ENDIAN_SHIFT) |
	    (7 << AML_SDXC_CNTRL_RX_ENDIAN_SHIFT) |
	    (0xf << AML_SDXC_CNTRL_RX_PERIOD_SHIFT) |
	    (0x7f << AML_SDXC_CNTRL_RX_TIMEOUT_SHIFT);

	switch (ios->bus_width) {
	case bus_width_8:
		ctlr |= AML_SDXC_CNTRL_BUS_WIDTH_8;
		break;
	case bus_width_4:
		ctlr |= AML_SDXC_CNTRL_BUS_WIDTH_4;
		break;
	case bus_width_1:
		ctlr |= AML_SDXC_CNTRL_BUS_WIDTH_1;
		break;
	default:
		return (EINVAL);
	}

	CSR_WRITE_4(sc, AML_SDXC_CNTRL_REG, ctlr);

	/*
	 * Disable clocks and then clock module prior to setting desired values.
	 */
	cctlr = CSR_READ_4(sc, AML_SDXC_CLK_CNTRL_REG);
	cctlr &= ~(AML_SDXC_CLK_CNTRL_TX_CLK_EN | AML_SDXC_CLK_CNTRL_RX_CLK_EN |
	    AML_SDXC_CLK_CNTRL_SD_CLK_EN);
	CSR_WRITE_4(sc, AML_SDXC_CLK_CNTRL_REG, cctlr);
	CSR_BARRIER(sc, AML_SDXC_CLK_CNTRL_REG);
	cctlr &= ~AML_SDXC_CLK_CNTRL_CLK_MODULE_EN;
	CSR_WRITE_4(sc, AML_SDXC_CLK_CNTRL_REG, cctlr);
	CSR_BARRIER(sc, AML_SDXC_CLK_CNTRL_REG);

	/*
	 *                  aml8726-m8
	 *
	 * Clock select 1   fclk_div2 (1.275 GHz)
	 */
	cctlr &= ~AML_SDXC_CLK_CNTRL_CLK_SEL_MASK;
	cctlr |= (1 << AML_SDXC_CLK_CNTRL_CLK_SEL_SHIFT);

	divisor = sc->ref_freq / ios->clock - 1;
	if (divisor == 0 || divisor == -1)
		divisor = 1;
	if ((sc->ref_freq / (divisor + 1)) > ios->clock)
		divisor += 1;
	if (divisor > (AML_SDXC_CLK_CNTRL_CLK_DIV_MASK >>
	    AML_SDXC_CLK_CNTRL_CLK_DIV_SHIFT))
		divisor = AML_SDXC_CLK_CNTRL_CLK_DIV_MASK >>
		    AML_SDXC_CLK_CNTRL_CLK_DIV_SHIFT;

	cctlr &= ~AML_SDXC_CLK_CNTRL_CLK_DIV_MASK;
	cctlr |= divisor << AML_SDXC_CLK_CNTRL_CLK_DIV_SHIFT;

	cctlr &= ~AML_SDXC_CLK_CNTRL_MEM_PWR_MASK;
	cctlr |= AML_SDXC_CLK_CNTRL_MEM_PWR_ON;

	CSR_WRITE_4(sc, AML_SDXC_CLK_CNTRL_REG, cctlr);
	CSR_BARRIER(sc, AML_SDXC_CLK_CNTRL_REG);

	/*
	 * Enable clock module and then clocks after setting desired values.
	 */
	cctlr |= AML_SDXC_CLK_CNTRL_CLK_MODULE_EN;
	CSR_WRITE_4(sc, AML_SDXC_CLK_CNTRL_REG, cctlr);
	CSR_BARRIER(sc, AML_SDXC_CLK_CNTRL_REG);
	cctlr |= AML_SDXC_CLK_CNTRL_TX_CLK_EN | AML_SDXC_CLK_CNTRL_RX_CLK_EN |
	    AML_SDXC_CLK_CNTRL_SD_CLK_EN;
	CSR_WRITE_4(sc, AML_SDXC_CLK_CNTRL_REG, cctlr);
	CSR_BARRIER(sc, AML_SDXC_CLK_CNTRL_REG);

	freq = sc->ref_freq / divisor;

	for (i = 0; aml8726_sdxc_clk_phases[i].voltage; i++) {
		if ((aml8726_sdxc_clk_phases[i].voltage &
		    (1 << ios->vdd)) != 0 &&
		    freq > aml8726_sdxc_clk_phases[i].freq)
			break;
		if (aml8726_sdxc_clk_phases[i].freq == 0)
			break;
	}

	clk2r = (1 << AML_SDXC_CLK2_SD_PHASE_SHIFT) |
	    (aml8726_sdxc_clk_phases[i].rx_phase <<
	    AML_SDXC_CLK2_RX_PHASE_SHIFT);
	CSR_WRITE_4(sc, AML_SDXC_CLK2_REG, clk2r);
	CSR_BARRIER(sc, AML_SDXC_CLK2_REG);

	error = 0;

	switch (ios->power_mode) {
	case power_up:
		/*
		 * Configure and power on the regulator so that the
		 * voltage stabilizes prior to powering on the card.
		 */
		if (sc->vselect.dev != NULL) {
			for (i = 0; i < 2; i++)
				if ((sc->voltages[i] & (1 << ios->vdd)) != 0)
					break;
			if (i >= 2)
				return (EINVAL);
			error = GPIO_PIN_SET(sc->vselect.dev,
			    sc->vselect.pin, i);
		}
		break;
	case power_on:
		error = aml8726_sdxc_power_on(sc);
		if (error)
			break;

		if (sc->card_rst.dev != NULL) {
			if (GPIO_PIN_SET(sc->card_rst.dev, sc->card_rst.pin,
			    PIN_ON_FLAG(sc->card_rst.pol)) != 0 ||
			    GPIO_PIN_SETFLAGS(sc->card_rst.dev,
			    sc->card_rst.pin,
			    GPIO_PIN_OUTPUT) != 0)
				error = ENXIO;

			DELAY(5);

			if (GPIO_PIN_SET(sc->card_rst.dev, sc->card_rst.pin,
			    PIN_OFF_FLAG(sc->card_rst.pol)) != 0)
				error = ENXIO;

			DELAY(5);

			if (error) {
				device_printf(sc->dev,
				    "could not use gpio to reset card\n");
				break;
			}
		}
		break;
	case power_off:
		error = aml8726_sdxc_power_off(sc);
		break;
	default:
		return (EINVAL);
	}

	return (error);
}