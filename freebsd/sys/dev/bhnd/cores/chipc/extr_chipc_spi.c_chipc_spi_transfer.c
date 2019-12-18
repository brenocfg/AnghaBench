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
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; int tx_data_sz; int rx_data_sz; scalar_t__ rx_data; scalar_t__ tx_data; scalar_t__ rx_cmd; scalar_t__ tx_cmd; } ;
struct chipc_spi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_DEBUG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CHIPC_SPI_FLASHADDR ; 
 int /*<<< orphan*/  CHIPC_SPI_FLASHCTL ; 
 int EIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SPI_BARRIER_WRITE (struct chipc_spi_softc*) ; 
 int /*<<< orphan*/  SPI_WRITE (struct chipc_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chipc_spi_txrx (struct chipc_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct chipc_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
chipc_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct chipc_spi_softc	*sc;
	uint8_t		*buf_in;
	uint8_t		*buf_out;
	int		 i;

	sc = device_get_softc(dev);
	KASSERT(cmd->tx_cmd_sz == cmd->rx_cmd_sz,
	    ("TX/RX command sizes should be equal"));
	KASSERT(cmd->tx_data_sz == cmd->rx_data_sz,
	    ("TX/RX data sizes should be equal"));

	if (cmd->tx_cmd_sz == 0) {
		BHND_DEBUG_DEV(child, "size of command is ZERO");
		return (EIO);
	}

	SPI_BARRIER_WRITE(sc);
	SPI_WRITE(sc, CHIPC_SPI_FLASHADDR, 0);
	SPI_BARRIER_WRITE(sc);

	/*
	 * Transfer command
	 */
	buf_out = (uint8_t *)cmd->tx_cmd;
	buf_in = (uint8_t *)cmd->rx_cmd;
	for (i = 0; i < cmd->tx_cmd_sz; i++)
		 if (chipc_spi_txrx(sc, buf_out[i], &(buf_in[i])))
			 return (EIO);

	/*
	 * Receive/transmit data
	 */
	buf_out = (uint8_t *)cmd->tx_data;
	buf_in = (uint8_t *)cmd->rx_data;
	for (i = 0; i < cmd->tx_data_sz; i++)
		if (chipc_spi_txrx(sc, buf_out[i], &(buf_in[i])))
			return (EIO);

	/*
	 * Clear CS bit and whole control register
	 */
	SPI_BARRIER_WRITE(sc);
	SPI_WRITE(sc, CHIPC_SPI_FLASHCTL, 0);
	SPI_BARRIER_WRITE(sc);

	return (0);
}