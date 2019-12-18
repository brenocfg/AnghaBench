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
struct mpssas_softc {int flags; int /*<<< orphan*/  sc; int /*<<< orphan*/  sim; } ;

/* Variables and functions */
 int MPSSAS_QUEUE_FROZEN ; 
 int /*<<< orphan*/  MPS_INFO ; 
 int /*<<< orphan*/  mps_dprint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int) ; 

void
mpssas_release_simq_reinit(struct mpssas_softc *sassc)
{
	if (sassc->flags & MPSSAS_QUEUE_FROZEN) {
		sassc->flags &= ~MPSSAS_QUEUE_FROZEN;
		xpt_release_simq(sassc->sim, 1);
		mps_dprint(sassc->sc, MPS_INFO, "Unfreezing SIM queue\n");
	}
}