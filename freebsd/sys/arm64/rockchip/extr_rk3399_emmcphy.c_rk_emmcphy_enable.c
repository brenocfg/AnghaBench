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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct rk_emmcphy_softc {int /*<<< orphan*/  syscon; int /*<<< orphan*/ * clk; struct rk_emmcphy_conf* phy_conf; } ;
struct rk_emmcphy_conf {int dummy; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int ERANGE ; 
 int /*<<< orphan*/  GRF_EMMCPHY_CON0 ; 
 int /*<<< orphan*/  GRF_EMMCPHY_CON6 ; 
 int /*<<< orphan*/  GRF_EMMCPHY_STATUS ; 
 int PHYCTRL_CALDONE ; 
 int PHYCTRL_DLLRDY ; 
 int PHYCTRL_DR_TY ; 
 int PHYCTRL_ENDLL ; 
 int PHYCTRL_FRQSEL ; 
 int PHYCTRL_FRQSEL_100M ; 
 int PHYCTRL_FRQSEL_150M ; 
 int PHYCTRL_FRQSEL_200M ; 
 int PHYCTRL_FRQSEL_50M ; 
 int PHYCTRL_OTAPDLYENA ; 
 int PHYCTRL_OTAPDLYSEL ; 
 int PHYCTRL_PDB ; 
 int SHIFTIN (int,int) ; 
 int SYSCON_READ_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCON_WRITE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int clk_get_freq (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  compat_data ; 
 struct rk_emmcphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phynode_get_device (struct phynode*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 

__attribute__((used)) static int
rk_emmcphy_enable(struct phynode *phynode, bool enable)
{
	struct rk_emmcphy_softc *sc;
	device_t dev;
	intptr_t phy;
	uint64_t rate, frqsel;
	uint32_t mask, val;
	int error;

	dev = phynode_get_device(phynode);
	phy = phynode_get_id(phynode);
	sc = device_get_softc(dev);

	if (bootverbose)
		device_printf(dev, "Phy id: %ld\n", phy);

	if (phy != 0) {
		device_printf(dev, "Unknown phy: %ld\n", phy);
		return (ERANGE);
	}
	if (enable) {
		/* Drive strength */
		mask = PHYCTRL_DR_TY;
		val = SHIFTIN(0, PHYCTRL_DR_TY);
		SYSCON_WRITE_4(sc->syscon, GRF_EMMCPHY_CON6,
		    (mask << 16) | val);

		/* Enable output tap delay */
		mask = PHYCTRL_OTAPDLYENA | PHYCTRL_OTAPDLYSEL;
		val = PHYCTRL_OTAPDLYENA | SHIFTIN(4, PHYCTRL_OTAPDLYSEL);
		SYSCON_WRITE_4(sc->syscon, GRF_EMMCPHY_CON0,
		    (mask << 16) | val);
	}

	/* Power down PHY and disable DLL before making changes */
	mask = PHYCTRL_ENDLL | PHYCTRL_PDB;
	val = 0;
	SYSCON_WRITE_4(sc->syscon, GRF_EMMCPHY_CON6, (mask << 16) | val);

	if (enable == false)
		return (0);

	sc->phy_conf = (struct rk_emmcphy_conf *)ofw_bus_search_compatible(dev,
	    compat_data)->ocd_data;

	/* Get clock */
	error = clk_get_by_ofw_name(dev, 0, "emmcclk", &sc->clk);
	if (error != 0) {
		device_printf(dev, "cannot get emmcclk clock, continue\n");
		sc->clk = NULL;
	} else
		device_printf(dev, "got emmcclk clock\n");

	if (sc->clk) {
		error = clk_get_freq(sc->clk, &rate);
		if (error != 0) {
			device_printf(dev, "cannot get clock frequency\n");
			return (ENXIO);
		}
	} else
		rate = 0;

	if (rate != 0) {
		if (rate < 75000000)
			frqsel = PHYCTRL_FRQSEL_50M;
		else if (rate < 125000000)
			frqsel = PHYCTRL_FRQSEL_100M;
		else if (rate < 175000000)
			frqsel = PHYCTRL_FRQSEL_150M;
		else
			frqsel = PHYCTRL_FRQSEL_200M;
	} else
		frqsel = PHYCTRL_FRQSEL_200M;

	DELAY(3);

	/* Power up PHY */
	mask = PHYCTRL_PDB;
	val = PHYCTRL_PDB;
	SYSCON_WRITE_4(sc->syscon, GRF_EMMCPHY_CON6, (mask << 16) | val);

	/* Wait for calibration */
	DELAY(10);
	val = SYSCON_READ_4(sc->syscon, GRF_EMMCPHY_STATUS);
	if ((val & PHYCTRL_CALDONE) == 0) {
		device_printf(dev, "PHY calibration did not complete\n");
		return (ENXIO);
	}

	/* Set DLL frequency */
	mask = PHYCTRL_FRQSEL;
	val = SHIFTIN(frqsel, PHYCTRL_FRQSEL);
	SYSCON_WRITE_4(sc->syscon, GRF_EMMCPHY_CON0, (mask << 16) | val);

	/* Enable DLL */
	mask = PHYCTRL_ENDLL;
	val = PHYCTRL_ENDLL;
	SYSCON_WRITE_4(sc->syscon, GRF_EMMCPHY_CON6, (mask << 16) | val);

	if (rate != 0) {
		/*
		 * Rockchip RK3399 TRM V1.3 Part2.pdf says in page 698:
		 * After the DLL control loop reaches steady state a DLL
		 * ready signal is generated by the DLL circuits
		 * 'phyctrl_dllrdy'.
		 * The time from 'phyctrl_endll' to DLL ready signal
		 * 'phyctrl_dllrdy' varies with the clock frequency.
		 * At 200MHz clock frequency the DLL ready delay is 2.56us,
		 * at 100MHz clock frequency the DLL ready delay is 5.112us and
		 * at 50 MHz clock frequency the DLL ready delay is 10.231us.
		 * We could use safe values for wait, 12us, 8us, 6us and 4us
		 * respectively.
		 * However due to some unknown reason it is not working and
		 * DLL seems to take extra long time to lock.
		 * So we will use more safe value 50ms here.
		 */

		/* Wait for DLL ready */
		DELAY(50000);
		val = SYSCON_READ_4(sc->syscon, GRF_EMMCPHY_STATUS);
		if ((val & PHYCTRL_DLLRDY) == 0) {
			device_printf(dev, "DLL loop failed to lock\n");
			return (ENXIO);
		}
	}

	return (0);
}