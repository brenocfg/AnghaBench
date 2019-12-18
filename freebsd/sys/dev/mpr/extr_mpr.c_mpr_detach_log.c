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
struct mpr_softc {int /*<<< orphan*/ * mpr_log_eh; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpr_deregister_events (struct mpr_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mpr_detach_log(struct mpr_softc *sc)
{

	if (sc->mpr_log_eh != NULL)
		mpr_deregister_events(sc, sc->mpr_log_eh);
	return (0);
}