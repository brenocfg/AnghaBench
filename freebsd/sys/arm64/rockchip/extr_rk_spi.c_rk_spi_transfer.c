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
typedef  int /*<<< orphan*/  uint32_t ;
struct spi_command {int /*<<< orphan*/  tx_data_sz; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  tx_cmd_sz; int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  rx_cmd; } ;
struct rk_spi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RK_SPI_LOCK (struct rk_spi_softc*) ; 
 int /*<<< orphan*/  RK_SPI_UNLOCK (struct rk_spi_softc*) ; 
 struct rk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_spi_enable_chip (struct rk_spi_softc*,int) ; 
 int /*<<< orphan*/  rk_spi_hw_setup (struct rk_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rk_spi_set_cs (struct rk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int rk_spi_xfer_buf (struct rk_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spibus_get_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spibus_get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rk_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct rk_spi_softc *sc;
	uint32_t cs, mode, clock;
	int err = 0;

	sc = device_get_softc(dev);

	spibus_get_cs(child, &cs);
	spibus_get_clock(child, &clock);
	spibus_get_mode(child, &mode);

	RK_SPI_LOCK(sc);
	rk_spi_hw_setup(sc, mode, clock);
	rk_spi_enable_chip(sc, 1);
	err = rk_spi_set_cs(sc, cs, true);
	if (err != 0) {
		rk_spi_enable_chip(sc, 0);
		RK_SPI_UNLOCK(sc);
		return (err);
	}

	/* Transfer command then data bytes. */
	err = 0;
	if (cmd->tx_cmd_sz > 0)
		err = rk_spi_xfer_buf(sc, cmd->rx_cmd, cmd->tx_cmd,
		    cmd->tx_cmd_sz);
	if (cmd->tx_data_sz > 0 && err == 0)
		err = rk_spi_xfer_buf(sc, cmd->rx_data, cmd->tx_data,
		    cmd->tx_data_sz);

	rk_spi_set_cs(sc, cs, false);
	rk_spi_enable_chip(sc, 0);
	RK_SPI_UNLOCK(sc);

	return (err);
}