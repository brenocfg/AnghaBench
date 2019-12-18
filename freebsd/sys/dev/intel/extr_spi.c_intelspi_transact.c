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
struct intelspi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTELSPI_ASSERT_LOCKED (struct intelspi_softc*) ; 
 int /*<<< orphan*/  intelspi_drain_rx_fifo (struct intelspi_softc*) ; 
 int /*<<< orphan*/  intelspi_fill_tx_fifo (struct intelspi_softc*) ; 
 int intelspi_transaction_done (struct intelspi_softc*) ; 

__attribute__((used)) static int
intelspi_transact(struct intelspi_softc *sc)
{

	INTELSPI_ASSERT_LOCKED(sc);

	/* TX - Fill up the FIFO. */
	intelspi_fill_tx_fifo(sc);

	/* RX - Drain the FIFO. */
	intelspi_drain_rx_fifo(sc);

	/* Check for end of transfer. */
	return intelspi_transaction_done(sc);
}