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
struct mv_spi_softc {int /*<<< orphan*/  sc_written; struct spi_command* sc_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_SPI_DATAOUT ; 
 int /*<<< orphan*/  MV_SPI_WRITE (struct mv_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
mv_spi_tx_byte(struct mv_spi_softc *sc)
{
	struct spi_command *cmd;
	uint32_t written;
	uint8_t *p;

	cmd = sc->sc_cmd; 
	p = (uint8_t *)cmd->tx_cmd;
	written = sc->sc_written++;
	if (written >= cmd->tx_cmd_sz) {
		p = (uint8_t *)cmd->tx_data;
		written -= cmd->tx_cmd_sz;
	}
	MV_SPI_WRITE(sc, MV_SPI_DATAOUT, p[written]);
}