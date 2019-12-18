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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;
struct fsl_sdhci_softc {int r1bfix_type; TYPE_1__ slot; int /*<<< orphan*/  mem_res; scalar_t__ r1bfix_timeout_at; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
#define  R1BFIX_AC12 129 
#define  R1BFIX_NODATA 128 
 int RD4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int SBT_1MS ; 
 int SDHCI_INT_DATA_END ; 
 int SDHCI_INT_RESPONSE ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  WR4 (struct fsl_sdhci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sdhci_r1bfix_is_wait_done (struct fsl_sdhci_softc*) ; 
 scalar_t__ getsbinuptime () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_generic_intr (TYPE_1__*) ; 

__attribute__((used)) static void
fsl_sdhci_intr(void *arg)
{
	struct fsl_sdhci_softc *sc = arg;
	uint32_t intmask;

	mtx_lock(&sc->slot.mtx);

	/*
	 * Manually check the DAT0 line for R1B response types that the
	 * controller fails to handle properly.  The controller asserts the done
	 * interrupt while the card is still asserting busy with the DAT0 line.
	 *
	 * We check DAT0 immediately because most of the time, especially on a
	 * read, the card will actually be done by time we get here.  If it's
	 * not, then the wait_done routine will schedule a callout to re-check
	 * periodically until it is done.  In that case we clear the interrupt
	 * out of the hardware now so that we can present it later when the DAT0
	 * line is released.
	 *
	 * If we need to wait for the DAT0 line to be released, we set up a
	 * timeout point 250ms in the future.  This number comes from the SD
	 * spec, which allows a command to take that long.  In the real world,
	 * cards tend to take 10-20ms for a long-running command such as a write
	 * or erase that spans two pages.
	 */
	switch (sc->r1bfix_type) {
	case R1BFIX_NODATA:
		intmask = RD4(sc, SDHCI_INT_STATUS) & SDHCI_INT_RESPONSE;
		break;
	case R1BFIX_AC12:
		intmask = RD4(sc, SDHCI_INT_STATUS) & SDHCI_INT_DATA_END;
		break;
	default:
		intmask = 0;
		break;
	}
	if (intmask) {
		sc->r1bfix_timeout_at = getsbinuptime() + 250 * SBT_1MS;
		if (!fsl_sdhci_r1bfix_is_wait_done(sc)) {
			WR4(sc, SDHCI_INT_STATUS, intmask);
			bus_barrier(sc->mem_res, SDHCI_INT_STATUS, 4, 
			    BUS_SPACE_BARRIER_WRITE);
		}
	}

	mtx_unlock(&sc->slot.mtx);
	sdhci_generic_intr(&sc->slot);
}