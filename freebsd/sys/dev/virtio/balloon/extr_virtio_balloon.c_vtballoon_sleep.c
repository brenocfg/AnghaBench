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
typedef  scalar_t__ uint32_t ;
struct vtballoon_softc {scalar_t__ vtballoon_current_npages; int vtballoon_flags; int vtballoon_timeout; scalar_t__ vtballoon_desired_npages; } ;

/* Variables and functions */
 int VTBALLOON_FLAG_DETACH ; 
 int /*<<< orphan*/  VTBALLOON_LOCK (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_MTX (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_UNLOCK (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  msleep (struct vtballoon_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ vtballoon_desired_size (struct vtballoon_softc*) ; 

__attribute__((used)) static int
vtballoon_sleep(struct vtballoon_softc *sc)
{
	int rc, timeout;
	uint32_t current, desired;

	rc = 0;
	current = sc->vtballoon_current_npages;

	VTBALLOON_LOCK(sc);
	for (;;) {
		if (sc->vtballoon_flags & VTBALLOON_FLAG_DETACH) {
			rc = 1;
			break;
		}

		desired = vtballoon_desired_size(sc);
		sc->vtballoon_desired_npages = desired;

		/*
		 * If given, use non-zero timeout on the first time through
		 * the loop. On subsequent times, timeout will be zero so
		 * we will reevaluate the desired size of the balloon and
		 * break out to retry if needed.
		 */
		timeout = sc->vtballoon_timeout;
		sc->vtballoon_timeout = 0;

		if (current > desired)
			break;
		if (current < desired && timeout == 0)
			break;

		msleep(sc, VTBALLOON_MTX(sc), 0, "vtbslp", timeout);
	}
	VTBALLOON_UNLOCK(sc);

	return (rc);
}