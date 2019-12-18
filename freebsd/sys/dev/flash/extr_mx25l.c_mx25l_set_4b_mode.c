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
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; struct spi_command* rx_cmd; struct spi_command* tx_cmd; } ;
typedef  struct spi_command uint8_t ;
typedef  int /*<<< orphan*/  txBuf ;
struct mx25l_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_parent; } ;
typedef  int /*<<< orphan*/  rxBuf ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 
 int /*<<< orphan*/  memset (struct spi_command*,int /*<<< orphan*/ ,int) ; 
 int mx25l_wait_for_device_ready (struct mx25l_softc*) ; 

__attribute__((used)) static int
mx25l_set_4b_mode(struct mx25l_softc *sc, uint8_t command)
{
	uint8_t txBuf[1], rxBuf[1];
	struct spi_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));

	cmd.tx_cmd_sz = cmd.rx_cmd_sz = 1;

	cmd.tx_cmd = txBuf;
	cmd.rx_cmd = rxBuf;

	txBuf[0] = command;

	if ((err = SPIBUS_TRANSFER(sc->sc_parent, sc->sc_dev, &cmd)) == 0)
		err = mx25l_wait_for_device_ready(sc);

	return (err);
}