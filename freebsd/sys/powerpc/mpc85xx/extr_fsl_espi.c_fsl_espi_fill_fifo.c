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
struct fsl_espi_softc {scalar_t__ sc_written; scalar_t__ sc_len; struct spi_command* sc_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESPI_SPIE ; 
 size_t ESPI_SPIE_TNF ; 
 int /*<<< orphan*/  ESPI_SPITF ; 
 size_t FSL_ESPI_READ (struct fsl_espi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSL_ESPI_WRITE_FIFO (struct fsl_espi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsl_espi_fill_fifo(struct fsl_espi_softc *sc)
{
	struct spi_command *cmd;
	uint32_t spier, written;
	uint8_t *data;

	cmd = sc->sc_cmd;
	spier = FSL_ESPI_READ(sc, ESPI_SPIE);
	while (sc->sc_written < sc->sc_len &&
	    (spier & ESPI_SPIE_TNF)) {
		data = (uint8_t *)cmd->tx_cmd;
		written = sc->sc_written++;
		if (written >= cmd->tx_cmd_sz) {
			data = (uint8_t *)cmd->tx_data;
			written -= cmd->tx_cmd_sz;
		}
		FSL_ESPI_WRITE_FIFO(sc, ESPI_SPITF, data[written]);
		spier = FSL_ESPI_READ(sc, ESPI_SPIE);
	}
}