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
struct ahc_softc {int /*<<< orphan*/ * pending_device; int /*<<< orphan*/  pending_scbs; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_pause_and_flushwork (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_shutdown (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 

int
ahc_suspend(struct ahc_softc *ahc)
{

	ahc_pause_and_flushwork(ahc);

	if (LIST_FIRST(&ahc->pending_scbs) != NULL) {
		ahc_unpause(ahc);
		return (EBUSY);
	}

#ifdef AHC_TARGET_MODE
	/*
	 * XXX What about ATIOs that have not yet been serviced?
	 * Perhaps we should just refuse to be suspended if we
	 * are acting in a target role.
	 */
	if (ahc->pending_device != NULL) {
		ahc_unpause(ahc);
		return (EBUSY);
	}
#endif
	ahc_shutdown(ahc);
	return (0);
}