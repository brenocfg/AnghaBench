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
struct intelspi_softc {scalar_t__ sc_read; scalar_t__ sc_len; struct spi_command* sc_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTELSPI_ASSERT_LOCKED (struct intelspi_softc*) ; 
 int INTELSPI_READ (struct intelspi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTELSPI_SSPREG_SSDR ; 
 int /*<<< orphan*/  intelspi_rxfifo_empty (struct intelspi_softc*) ; 

__attribute__((used)) static void
intelspi_drain_rx_fifo(struct intelspi_softc *sc)
{
	struct spi_command *cmd;
	uint32_t  read;
	uint8_t *data;

	INTELSPI_ASSERT_LOCKED(sc);

	cmd = sc->sc_cmd;
	while (sc->sc_read < sc->sc_len &&
	    !intelspi_rxfifo_empty(sc)) {
		data = (uint8_t *)cmd->rx_cmd;
		read = sc->sc_read++;
		if (read >= cmd->rx_cmd_sz) {
			data = (uint8_t *)cmd->rx_data;
			read -= cmd->rx_cmd_sz;
		}
		data[read] = INTELSPI_READ(sc, INTELSPI_SSPREG_SSDR) & 0xff;
	}
}