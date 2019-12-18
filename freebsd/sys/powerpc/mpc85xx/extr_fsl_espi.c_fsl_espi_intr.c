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
struct fsl_espi_softc {int sc_flags; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESPI_SPIE ; 
 int ESPI_SPIE_DON ; 
 int FSL_ESPI_BUSY ; 
 int /*<<< orphan*/  FSL_ESPI_LOCK (struct fsl_espi_softc*) ; 
 int FSL_ESPI_READ (struct fsl_espi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSL_ESPI_UNLOCK (struct fsl_espi_softc*) ; 
 int /*<<< orphan*/  FSL_ESPI_WRITE (struct fsl_espi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsl_espi_drain_fifo (struct fsl_espi_softc*) ; 
 int /*<<< orphan*/  fsl_espi_fill_fifo (struct fsl_espi_softc*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsl_espi_intr(void *arg)
{
	struct fsl_espi_softc *sc;
	uint32_t spie;

	sc = (struct fsl_espi_softc *)arg;
	FSL_ESPI_LOCK(sc);

	/* Filter stray interrupts. */
	if ((sc->sc_flags & FSL_ESPI_BUSY) == 0) {
		FSL_ESPI_UNLOCK(sc);
		return;
	}
	spie = FSL_ESPI_READ(sc, ESPI_SPIE);
	FSL_ESPI_WRITE(sc, ESPI_SPIE, spie);

	/* TX - Fill up the FIFO. */
	fsl_espi_fill_fifo(sc);

	/* RX - Drain the FIFO. */
	fsl_espi_drain_fifo(sc);

	/* Check for end of transfer. */
	if (spie & ESPI_SPIE_DON)
		wakeup(sc->sc_dev);

	FSL_ESPI_UNLOCK(sc);
}