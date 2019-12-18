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
struct sbp_targ_softc {int /*<<< orphan*/  sim; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_FREEZED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sbp_targ_post_explore(void *arg)
{
	struct sbp_targ_softc *sc;

	sc = (struct sbp_targ_softc *)arg;
	sc->flags &= ~F_FREEZED;
	xpt_release_simq(sc->sim, /*run queue*/TRUE);
	return;
}