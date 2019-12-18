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
typedef  int uint32_t ;
struct intelspi_softc {scalar_t__ sc_written; scalar_t__ sc_len; scalar_t__ sc_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTELSPI_ASSERT_LOCKED (struct intelspi_softc*) ; 
 int INTELSPI_READ (struct intelspi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTELSPI_SSPREG_SSSR ; 
 int SSSR_RNE ; 
 int SSSR_TFL_MASK ; 
 int SSSR_TNF ; 

__attribute__((used)) static int
intelspi_transaction_done(struct intelspi_softc *sc)
{
	int txfifo_empty;
	uint32_t sssr;

	INTELSPI_ASSERT_LOCKED(sc);

	if (sc->sc_written != sc->sc_len ||
	    sc->sc_read != sc->sc_len)
		return (0);

	sssr = INTELSPI_READ(sc, INTELSPI_SSPREG_SSSR);
	txfifo_empty = ((sssr & SSSR_TFL_MASK) == 0) &&
		(sssr & SSSR_TNF);

	if (txfifo_empty && !(sssr & SSSR_RNE))
		return (1);

	return (0);
}