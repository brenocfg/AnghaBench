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
typedef  int uint8_t ;
struct spi_command {int* tx_cmd; int* rx_cmd; int rx_cmd_sz; int tx_cmd_sz; } ;
struct mx25l_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_parent; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int CMD_READ_STATUS ; 
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 
 int STATUS_WIP ; 
 int /*<<< orphan*/  memset (struct spi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mx25l_wait_for_device_ready(struct mx25l_softc *sc)
{
	uint8_t txBuf[2], rxBuf[2];
	struct spi_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));

	do {
		txBuf[0] = CMD_READ_STATUS;
		cmd.tx_cmd = txBuf;
		cmd.rx_cmd = rxBuf;
		cmd.rx_cmd_sz = 2;
		cmd.tx_cmd_sz = 2;
		err = SPIBUS_TRANSFER(sc->sc_parent, sc->sc_dev, &cmd);
	} while (err == 0 && (rxBuf[1] & STATUS_WIP));

	return (err);
}