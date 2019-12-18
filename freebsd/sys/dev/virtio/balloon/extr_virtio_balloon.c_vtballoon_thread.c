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
struct vtballoon_softc {scalar_t__ vtballoon_current_npages; scalar_t__ vtballoon_desired_npages; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  vtballoon_deflate (struct vtballoon_softc*,scalar_t__) ; 
 int /*<<< orphan*/  vtballoon_inflate (struct vtballoon_softc*,scalar_t__) ; 
 scalar_t__ vtballoon_sleep (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  vtballoon_update_size (struct vtballoon_softc*) ; 

__attribute__((used)) static void
vtballoon_thread(void *xsc)
{
	struct vtballoon_softc *sc;
	uint32_t current, desired;

	sc = xsc;

	for (;;) {
		if (vtballoon_sleep(sc) != 0)
			break;

		current = sc->vtballoon_current_npages;
		desired = sc->vtballoon_desired_npages;

		if (desired != current) {
			if (desired > current)
				vtballoon_inflate(sc, desired - current);
			else
				vtballoon_deflate(sc, current - desired);

			vtballoon_update_size(sc);
		}
	}

	kthread_exit();
}