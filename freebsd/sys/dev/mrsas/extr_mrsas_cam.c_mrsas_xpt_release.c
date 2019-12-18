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
struct mrsas_softc {int /*<<< orphan*/  sim_1; int /*<<< orphan*/  sim_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int) ; 

void
mrsas_xpt_release(struct mrsas_softc *sc)
{
	xpt_release_simq(sc->sim_0, 1);
	xpt_release_simq(sc->sim_1, 1);
}