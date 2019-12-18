#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; int* tx_cmd; int* rx_cmd; int tx_data_sz; int rx_data_sz; void* rx_data; void* tx_data; } ;
struct mx25l_softc {int sc_flags; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_parent; TYPE_1__* sc_disk; } ;
typedef  int off_t ;
typedef  void* caddr_t ;
struct TYPE_2__ {int d_sectorsize; } ;

/* Variables and functions */
 int CMD_FAST_READ ; 
 int EIO ; 
 int FL_ENABLE_4B_ADDR ; 
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 

__attribute__((used)) static int
mx25l_read(struct mx25l_softc *sc, off_t offset, caddr_t data, off_t count)
{
	uint8_t txBuf[8], rxBuf[8];
	struct spi_command cmd;
	int err = 0;

	/*
	 * Enforce that reads are aligned to the disk sectorsize, not the
	 * erase sectorsize.  In this way, smaller read IO is possible,
	 * dramatically speeding up filesystem/geom_compress access.
	 */
	if (count % sc->sc_disk->d_sectorsize != 0 ||
	    offset % sc->sc_disk->d_sectorsize != 0)
		return (EIO);

	txBuf[0] = CMD_FAST_READ;
	if (sc->sc_flags & FL_ENABLE_4B_ADDR) {
		cmd.tx_cmd_sz = 6;
		cmd.rx_cmd_sz = 6;

		txBuf[1] = (offset >> 24) & 0xff;
		txBuf[2] = (offset >> 16) & 0xff;
		txBuf[3] = (offset >> 8) & 0xff;
		txBuf[4] = offset & 0xff;
		/* Dummy byte */
		txBuf[5] = 0;
	} else {
		cmd.tx_cmd_sz = 5;
		cmd.rx_cmd_sz = 5;

		txBuf[1] = (offset >> 16) & 0xff;
		txBuf[2] = (offset >> 8) & 0xff;
		txBuf[3] = offset & 0xff;
		/* Dummy byte */
		txBuf[4] = 0;
	}

	cmd.tx_cmd = txBuf;
	cmd.rx_cmd = rxBuf;
	cmd.tx_data = data;
	cmd.rx_data = data;
	cmd.tx_data_sz = count;
	cmd.rx_data_sz = count;

	err = SPIBUS_TRANSFER(sc->sc_parent, sc->sc_dev, &cmd);
	return (err);
}