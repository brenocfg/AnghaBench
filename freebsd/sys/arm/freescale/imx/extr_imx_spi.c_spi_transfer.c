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
typedef  size_t uint32_t ;
struct spi_softc {int debug; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** cspins; } ;
struct spi_command {int /*<<< orphan*/  tx_data_sz; int /*<<< orphan*/  tx_data; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  tx_cmd_sz; int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  rx_cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t CS_MAX ; 
 int /*<<< orphan*/  ECSPI_CTLREG ; 
 int EINVAL ; 
 int /*<<< orphan*/  WR4 (struct spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 struct spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_hw_setup (struct spi_softc*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  spi_set_chipsel (struct spi_softc*,size_t,int) ; 
 int spi_xfer_buf (struct spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spibus_get_clock (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  spibus_get_mode (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct spi_softc *sc = device_get_softc(dev);
	uint32_t cs, mode, clock;
	int err;

	spibus_get_cs(child, &cs);
	spibus_get_clock(child, &clock);
	spibus_get_mode(child, &mode);

	if (cs > CS_MAX || sc->cspins[cs] == NULL) {
		if (sc->debug || bootverbose)
			device_printf(sc->dev, "Invalid chip select %u\n", cs);
		return (EINVAL);
	}

	mtx_lock(&sc->mtx);
	device_busy(sc->dev);

	if (sc->debug >= 1) {
		device_printf(sc->dev,
		    "spi_transfer, cs 0x%x clock %u mode %u\n",
		    cs, clock, mode);
	}

	/* Set up the hardware and select the device. */
	spi_hw_setup(sc, cs, mode, clock);
	spi_set_chipsel(sc, cs, true);

	/* Transfer command then data bytes. */
	err = 0;
	if (cmd->tx_cmd_sz > 0)
		err = spi_xfer_buf(sc, cmd->rx_cmd, cmd->tx_cmd,
		    cmd->tx_cmd_sz);
	if (cmd->tx_data_sz > 0 && err == 0)
		err = spi_xfer_buf(sc, cmd->rx_data, cmd->tx_data,
		    cmd->tx_data_sz);

	/* Deselect the device, turn off (and reset) hardware. */
	spi_set_chipsel(sc, cs, false);
	WR4(sc, ECSPI_CTLREG, 0);

	device_unbusy(sc->dev);
	mtx_unlock(&sc->mtx);

	return (err);
}