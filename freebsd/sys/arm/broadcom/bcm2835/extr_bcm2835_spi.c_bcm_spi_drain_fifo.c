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
typedef  size_t uint32_t ;
struct spi_command {size_t rx_cmd_sz; scalar_t__ rx_data; scalar_t__ rx_cmd; } ;
struct bcm_spi_softc {scalar_t__ sc_read; scalar_t__ sc_len; struct spi_command* sc_cmd; } ;

/* Variables and functions */
 size_t BCM_SPI_READ (struct bcm_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_CS ; 
 size_t SPI_CS_RXD ; 
 int /*<<< orphan*/  SPI_FIFO ; 

__attribute__((used)) static void
bcm_spi_drain_fifo(struct bcm_spi_softc *sc)
{
	struct spi_command *cmd;
	uint32_t cs, read;
	uint8_t *data;

	cmd = sc->sc_cmd;
	cs = BCM_SPI_READ(sc, SPI_CS) & SPI_CS_RXD;
	while (sc->sc_read < sc->sc_len && cs == SPI_CS_RXD) {
		data = (uint8_t *)cmd->rx_cmd;
		read = sc->sc_read++;
		if (read >= cmd->rx_cmd_sz) {
			data = (uint8_t *)cmd->rx_data;
			read -= cmd->rx_cmd_sz;
		}
		data[read] = BCM_SPI_READ(sc, SPI_FIFO) & 0xff;
		cs = BCM_SPI_READ(sc, SPI_CS) & SPI_CS_RXD;
	}
}