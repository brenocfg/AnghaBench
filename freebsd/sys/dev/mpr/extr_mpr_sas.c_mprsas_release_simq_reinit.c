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
struct mprsas_softc {int flags; int /*<<< orphan*/  sc; int /*<<< orphan*/  sim; } ;

/* Variables and functions */
 int MPRSAS_QUEUE_FROZEN ; 
 int /*<<< orphan*/  MPR_INFO ; 
 int /*<<< orphan*/  mpr_dprint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int) ; 

void
mprsas_release_simq_reinit(struct mprsas_softc *sassc)
{
	if (sassc->flags & MPRSAS_QUEUE_FROZEN) {
		sassc->flags &= ~MPRSAS_QUEUE_FROZEN;
		xpt_release_simq(sassc->sim, 1);
		mpr_dprint(sassc->sc, MPR_INFO, "Unfreezing SIM queue\n");
	}
}