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
typedef  int /*<<< orphan*/  uint32_t ;
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; int tx_data_sz; int rx_data_sz; scalar_t__ rx_data; scalar_t__ tx_data; scalar_t__ rx_cmd; scalar_t__ tx_cmd; } ;
struct ar71xx_spi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SPIBUS_CS_HIGH ; 
 int /*<<< orphan*/  ar71xx_spi_chip_activate (struct ar71xx_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_spi_chip_deactivate (struct ar71xx_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_spi_txrx (struct ar71xx_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ar71xx_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ar71xx_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct ar71xx_spi_softc *sc;
	uint32_t cs;
	uint8_t *buf_in, *buf_out;
	int i;

	sc = device_get_softc(dev);

	spibus_get_cs(child, &cs);

	cs &= ~SPIBUS_CS_HIGH;

	ar71xx_spi_chip_activate(sc, cs);

	KASSERT(cmd->tx_cmd_sz == cmd->rx_cmd_sz, 
	    ("TX/RX command sizes should be equal"));
	KASSERT(cmd->tx_data_sz == cmd->rx_data_sz, 
	    ("TX/RX data sizes should be equal"));

	/*
	 * Transfer command
	 */
	buf_out = (uint8_t *)cmd->tx_cmd;
	buf_in = (uint8_t *)cmd->rx_cmd;
	for (i = 0; i < cmd->tx_cmd_sz; i++)
		buf_in[i] = ar71xx_spi_txrx(sc, cs, buf_out[i]);

	/*
	 * Receive/transmit data (depends on  command)
	 */
	buf_out = (uint8_t *)cmd->tx_data;
	buf_in = (uint8_t *)cmd->rx_data;
	for (i = 0; i < cmd->tx_data_sz; i++)
		buf_in[i] = ar71xx_spi_txrx(sc, cs, buf_out[i]);

	ar71xx_spi_chip_deactivate(sc, cs);

	return (0);
}