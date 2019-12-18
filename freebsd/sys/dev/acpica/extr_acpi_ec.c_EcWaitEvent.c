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
typedef  scalar_t__ u_int ;
struct acpi_ec_softc {scalar_t__ ec_gencount; int /*<<< orphan*/  ec_dev; scalar_t__ ec_suspending; } ;
typedef  int /*<<< orphan*/  EC_EVENT ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NO_HARDWARE_RESPONSE ; 
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EC_POLL_DELAY ; 
 int /*<<< orphan*/  EcCheckStatus (struct acpi_ec_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_ACPI ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ec ; 
 int ec_polled_mode ; 
 int ec_timeout ; 
 int hz ; 
 scalar_t__ rebooting ; 
 int /*<<< orphan*/  tsleep (struct acpi_ec_softc*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ACPI_STATUS
EcWaitEvent(struct acpi_ec_softc *sc, EC_EVENT Event, u_int gen_count)
{
    static int	no_intr = 0;
    ACPI_STATUS	Status;
    int		count, i, need_poll, slp_ival;

    ACPI_SERIAL_ASSERT(ec);
    Status = AE_NO_HARDWARE_RESPONSE;
    need_poll = cold || rebooting || ec_polled_mode || sc->ec_suspending;

    /* Wait for event by polling or GPE (interrupt). */
    if (need_poll) {
	count = (ec_timeout * 1000) / EC_POLL_DELAY;
	if (count == 0)
	    count = 1;
	DELAY(10);
	for (i = 0; i < count; i++) {
	    Status = EcCheckStatus(sc, "poll", Event);
	    if (ACPI_SUCCESS(Status))
		break;
	    DELAY(EC_POLL_DELAY);
	}
    } else {
	slp_ival = hz / 1000;
	if (slp_ival != 0) {
	    count = ec_timeout;
	} else {
	    /* hz has less than 1 ms resolution so scale timeout. */
	    slp_ival = 1;
	    count = ec_timeout / (1000 / hz);
	}

	/*
	 * Wait for the GPE to signal the status changed, checking the
	 * status register each time we get one.  It's possible to get a
	 * GPE for an event we're not interested in here (i.e., SCI for
	 * EC query).
	 */
	for (i = 0; i < count; i++) {
	    if (gen_count == sc->ec_gencount)
		tsleep(sc, 0, "ecgpe", slp_ival);
	    /*
	     * Record new generation count.  It's possible the GPE was
	     * just to notify us that a query is needed and we need to
	     * wait for a second GPE to signal the completion of the
	     * event we are actually waiting for.
	     */
	    Status = EcCheckStatus(sc, "sleep", Event);
	    if (ACPI_SUCCESS(Status)) {
		if (gen_count == sc->ec_gencount)
		    no_intr++;
		else
		    no_intr = 0;
		break;
	    }
	    gen_count = sc->ec_gencount;
	}

	/*
	 * We finished waiting for the GPE and it never arrived.  Try to
	 * read the register once and trust whatever value we got.  This is
	 * the best we can do at this point.
	 */
	if (ACPI_FAILURE(Status))
	    Status = EcCheckStatus(sc, "sleep_end", Event);
    }
    if (!need_poll && no_intr > 10) {
	device_printf(sc->ec_dev,
	    "not getting interrupts, switched to polled mode\n");
	ec_polled_mode = 1;
    }
    if (ACPI_FAILURE(Status))
	    CTR0(KTR_ACPI, "error: ec wait timed out");
    return (Status);
}