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
typedef  size_t uint32_t ;
struct spi_command {size_t tx_cmd_sz; scalar_t__ tx_data; scalar_t__ tx_cmd; } ;
struct bcm_spi_softc {scalar_t__ sc_written; scalar_t__ sc_len; struct spi_command* sc_cmd; } ;

/* Variables and functions */
 size_t BCM_SPI_READ (struct bcm_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_SPI_WRITE (struct bcm_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CS ; 
 size_t SPI_CS_TA ; 
 size_t SPI_CS_TXD ; 
 int /*<<< orphan*/  SPI_FIFO ; 

__attribute__((used)) static void
bcm_spi_fill_fifo(struct bcm_spi_softc *sc)
{
	struct spi_command *cmd;
	uint32_t cs, written;
	uint8_t *data;

	cmd = sc->sc_cmd;
	cs = BCM_SPI_READ(sc, SPI_CS) & (SPI_CS_TA | SPI_CS_TXD);
	while (sc->sc_written < sc->sc_len &&
	    cs == (SPI_CS_TA | SPI_CS_TXD)) {
		data = (uint8_t *)cmd->tx_cmd;
		written = sc->sc_written++;
		if (written >= cmd->tx_cmd_sz) {
			data = (uint8_t *)cmd->tx_data;
			written -= cmd->tx_cmd_sz;
		}
		BCM_SPI_WRITE(sc, SPI_FIFO, data[written]);
		cs = BCM_SPI_READ(sc, SPI_CS) & (SPI_CS_TA | SPI_CS_TXD);
	}
}