#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atp_softc {int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_callout; } ;
struct TYPE_4__ {int flags; scalar_t__ age; scalar_t__ type; } ;
typedef  TYPE_1__ atp_stroke_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATP_DOUBLE_TAP_DRAG ; 
 scalar_t__ ATP_STROKE_SLIDE ; 
 int /*<<< orphan*/  ATP_ZOMBIES_EXIST ; 
 int /*<<< orphan*/  ATP_ZOMBIE_STROKE_REAP_INTERVAL ; 
 int ATSF_ZOMBIE ; 
 int /*<<< orphan*/  atp_free_stroke (struct atp_softc*,TYPE_1__*) ; 
 int /*<<< orphan*/  atp_reap_sibling_zombies ; 
 scalar_t__ atp_stroke_maturity_threshold ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct atp_softc*) ; 

__attribute__((used)) static void
atp_terminate_stroke(struct atp_softc *sc, atp_stroke_t *strokep)
{
	if (strokep->flags & ATSF_ZOMBIE)
		return;

	/* Drop immature strokes rightaway. */
	if (strokep->age <= atp_stroke_maturity_threshold) {
		atp_free_stroke(sc, strokep);
		return;
	}

	strokep->flags |= ATSF_ZOMBIE;
	sc->sc_state |= ATP_ZOMBIES_EXIST;

	callout_reset(&sc->sc_callout, ATP_ZOMBIE_STROKE_REAP_INTERVAL,
	    atp_reap_sibling_zombies, sc);

	/*
	 * Reset the double-click-n-drag at the termination of any
	 * slide stroke.
	 */
	if (strokep->type == ATP_STROKE_SLIDE)
		sc->sc_state &= ~ATP_DOUBLE_TAP_DRAG;
}