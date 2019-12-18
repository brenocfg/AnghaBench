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
struct spi_command {int rx_cmd_sz; int tx_cmd_sz; struct spi_command* rx_cmd; struct spi_command* tx_cmd; } ;
typedef  struct spi_command uint8_t ;
typedef  int /*<<< orphan*/  txBuf ;
struct mx25l_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_parent; } ;
typedef  int /*<<< orphan*/  rxBuf ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 struct spi_command CMD_WRITE_DISABLE ; 
 struct spi_command CMD_WRITE_ENABLE ; 
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 
 int /*<<< orphan*/  memset (struct spi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mx25l_set_writable(struct mx25l_softc *sc, int writable)
{
	uint8_t txBuf[1], rxBuf[1];
	struct spi_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));

	txBuf[0] = writable ? CMD_WRITE_ENABLE : CMD_WRITE_DISABLE;
	cmd.tx_cmd = txBuf;
	cmd.rx_cmd = rxBuf;
	cmd.rx_cmd_sz = 1;
	cmd.tx_cmd_sz = 1;
	err = SPIBUS_TRANSFER(sc->sc_parent, sc->sc_dev, &cmd);
	return (err);
}