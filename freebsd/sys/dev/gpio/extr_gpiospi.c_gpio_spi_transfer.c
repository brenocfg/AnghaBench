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
typedef  int /*<<< orphan*/  uint8_t ;
struct spibus_ivar {scalar_t__ mode; int /*<<< orphan*/  cs; } ;
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; int tx_data_sz; int rx_data_sz; scalar_t__ rx_data; scalar_t__ tx_data; scalar_t__ rx_cmd; scalar_t__ tx_cmd; } ;
struct gpio_spi_softc {int /*<<< orphan*/  sc_sclk; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_busdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOBUS_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct spibus_ivar* SPIBUS_IVAR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIBUS_MODE_CPHA ; 
 scalar_t__ SPIBUS_MODE_CPOL ; 
 struct gpio_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_spi_chip_activate (struct gpio_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_spi_chip_deactivate (struct gpio_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_spi_txrx (struct gpio_spi_softc*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpio_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct gpio_spi_softc *sc;
	uint8_t *buf_in, *buf_out;
	struct spibus_ivar *devi = SPIBUS_IVAR(child);
	int i;

	sc = device_get_softc(dev);

	KASSERT(cmd->tx_cmd_sz == cmd->rx_cmd_sz, 
	    ("TX/RX command sizes should be equal"));
	KASSERT(cmd->tx_data_sz == cmd->rx_data_sz, 
	    ("TX/RX data sizes should be equal"));

	gpio_spi_chip_activate(sc, devi->cs);

	/* Preset pins */
	if ((devi->mode == SPIBUS_MODE_CPOL) ||
	    (devi->mode == SPIBUS_MODE_CPHA)) {
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_sclk, 1);
	} else {
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_sclk, 0);
	}

	/*
	 * Transfer command
	 */
	buf_out = (uint8_t *)cmd->tx_cmd;
	buf_in = (uint8_t *)cmd->rx_cmd;

	for (i = 0; i < cmd->tx_cmd_sz; i++)
		buf_in[i] = gpio_spi_txrx(sc, devi->cs, devi->mode, buf_out[i]);

	/*
	 * Receive/transmit data (depends on command)
	 */
	buf_out = (uint8_t *)cmd->tx_data;
	buf_in = (uint8_t *)cmd->rx_data;
	for (i = 0; i < cmd->tx_data_sz; i++)
		buf_in[i] = gpio_spi_txrx(sc, devi->cs, devi->mode, buf_out[i]);

	/* Return pins to mode default */
	if ((devi->mode == SPIBUS_MODE_CPOL) ||
	    (devi->mode == SPIBUS_MODE_CPHA)) {
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_sclk, 1);
	} else {
		GPIOBUS_PIN_SET(sc->sc_busdev, sc->sc_dev,
		    sc->sc_sclk, 0);
	}

	gpio_spi_chip_deactivate(sc, devi->cs);

	return (0);
}