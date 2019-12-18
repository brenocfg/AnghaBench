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
struct ahd_softc {int /*<<< orphan*/  pending_scbs; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahd_pause_and_flushwork (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_shutdown (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 

int
ahd_suspend(struct ahd_softc *ahd)
{

	ahd_pause_and_flushwork(ahd);

	if (LIST_FIRST(&ahd->pending_scbs) != NULL) {
		ahd_unpause(ahd);
		return (EBUSY);
	}
	ahd_shutdown(ahd);
	return (0);
}