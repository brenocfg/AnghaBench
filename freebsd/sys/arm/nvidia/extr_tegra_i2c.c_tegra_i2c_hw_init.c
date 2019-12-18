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
struct tegra_i2c_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_freq; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I2C_CNFG ; 
 int I2C_CNFG_DEBOUNCE_CNT (int) ; 
 int I2C_CNFG_NEW_MASTER_FSM ; 
 int I2C_CNFG_PACKET_MODE_EN ; 
 int /*<<< orphan*/  I2C_CONFIG_LOAD ; 
 int I2C_CONFIG_LOAD_MSTR_CONFIG_LOAD ; 
 int /*<<< orphan*/  I2C_FIFO_CONTROL ; 
 int I2C_FIFO_CONTROL_RX_FIFO_TRIG (int /*<<< orphan*/ ) ; 
 int I2C_FIFO_CONTROL_TX_FIFO_TRIG (int) ; 
 int /*<<< orphan*/  I2C_INTERRUPT_MASK_REGISTER ; 
 int /*<<< orphan*/  I2C_INTERRUPT_STATUS_REGISTER ; 
 scalar_t__ RD4 (struct tegra_i2c_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct tegra_i2c_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hwreset_assert (int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_i2c_bus_clear (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  tegra_i2c_setup_clk (struct tegra_i2c_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_i2c_hw_init(struct tegra_i2c_softc *sc)
{
	int rv, timeout;

	/* Reset the core. */
	rv = hwreset_assert(sc->reset);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot assert reset\n");
		return (rv);
	}
	DELAY(10);
	rv = hwreset_deassert(sc->reset);
	if (rv != 0) {
		device_printf(sc->dev, "Cannot clear reset\n");
		return (rv);
	}

	WR4(sc, I2C_INTERRUPT_MASK_REGISTER, 0);
	WR4(sc, I2C_INTERRUPT_STATUS_REGISTER, 0xFFFFFFFF);
	WR4(sc, I2C_CNFG, I2C_CNFG_NEW_MASTER_FSM | I2C_CNFG_PACKET_MODE_EN |
	    I2C_CNFG_DEBOUNCE_CNT(2));

	tegra_i2c_setup_clk(sc, sc->bus_freq);

	WR4(sc, I2C_FIFO_CONTROL, I2C_FIFO_CONTROL_TX_FIFO_TRIG(7) |
	    I2C_FIFO_CONTROL_RX_FIFO_TRIG(0));

	WR4(sc, I2C_CONFIG_LOAD, I2C_CONFIG_LOAD_MSTR_CONFIG_LOAD);
	for (timeout = 1000; timeout > 0; timeout--) {
		if (RD4(sc, I2C_CONFIG_LOAD) == 0)
			break;
		DELAY(10);
	}
	if (timeout <= 0)
		device_printf(sc->dev, "config load timeouted\n");

	tegra_i2c_bus_clear(sc);
	return (0);
}