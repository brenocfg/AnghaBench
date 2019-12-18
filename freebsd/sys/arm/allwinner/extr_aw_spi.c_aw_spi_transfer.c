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
struct spi_command {int /*<<< orphan*/  rx_data_sz; int /*<<< orphan*/  tx_data_sz; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  rx_cmd_sz; int /*<<< orphan*/  tx_cmd_sz; int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  rx_cmd; } ;
struct aw_spi_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/  mod_freq; int /*<<< orphan*/  clk_mod; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_SPI_GCR ; 
 int AW_SPI_GCR_EN ; 
 int AW_SPI_GCR_SRST ; 
 int AW_SPI_MAX_CS ; 
 int AW_SPI_READ_4 (struct aw_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_SPI_WRITE_4 (struct aw_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int EINVAL ; 
 int SPIBUS_CS_HIGH ; 
 int /*<<< orphan*/  aw_spi_setup_clock (struct aw_spi_softc*,int) ; 
 int /*<<< orphan*/  aw_spi_setup_cs (struct aw_spi_softc*,int,int) ; 
 int /*<<< orphan*/  aw_spi_setup_mode (struct aw_spi_softc*,int) ; 
 int aw_spi_xfer (struct aw_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct aw_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spibus_get_clock (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spibus_get_mode (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
aw_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct aw_spi_softc *sc;
	uint32_t cs, mode, clock, reg;
	int err = 0;

	sc = device_get_softc(dev);

	spibus_get_cs(child, &cs);
	spibus_get_clock(child, &clock);
	spibus_get_mode(child, &mode);

	/* The minimum divider is 2 so set the clock at twice the needed speed */
	clk_set_freq(sc->clk_mod, 2 * clock, CLK_SET_ROUND_DOWN);
	clk_get_freq(sc->clk_mod, &sc->mod_freq);
	if (cs >= AW_SPI_MAX_CS) {
		device_printf(dev, "Invalid cs %d\n", cs);
		return (EINVAL);
	}

	mtx_lock(&sc->mtx);

	/* Enable and reset the module */
	reg = AW_SPI_READ_4(sc, AW_SPI_GCR);
	reg |= AW_SPI_GCR_EN | AW_SPI_GCR_SRST;
	AW_SPI_WRITE_4(sc, AW_SPI_GCR, reg);

	/* Setup clock, CS and mode */
	aw_spi_setup_clock(sc, clock);
	aw_spi_setup_mode(sc, mode);
	if (cs & SPIBUS_CS_HIGH)
		aw_spi_setup_cs(sc, cs, false);
	else
		aw_spi_setup_cs(sc, cs, true);

	/* xfer */
	err = 0;
	if (cmd->tx_cmd_sz > 0)
		err = aw_spi_xfer(sc, cmd->rx_cmd, cmd->tx_cmd,
		    cmd->tx_cmd_sz, cmd->rx_cmd_sz);
	if (cmd->tx_data_sz > 0 && err == 0)
		err = aw_spi_xfer(sc, cmd->rx_data, cmd->tx_data,
		    cmd->tx_data_sz, cmd->rx_data_sz);

	if (cs & SPIBUS_CS_HIGH)
		aw_spi_setup_cs(sc, cs, true);
	else
		aw_spi_setup_cs(sc, cs, false);

	/* Disable the module */
	reg = AW_SPI_READ_4(sc, AW_SPI_GCR);
	reg &= ~AW_SPI_GCR_EN;
	AW_SPI_WRITE_4(sc, AW_SPI_GCR, reg);

	mtx_unlock(&sc->mtx);

	return (err);
}