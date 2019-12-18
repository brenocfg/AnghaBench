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
struct pvscsi_softc {int frozen; int /*<<< orphan*/  sim; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pvscsi_freeze(struct pvscsi_softc *sc)
{

	if (!sc->frozen) {
		xpt_freeze_simq(sc->sim, 1);
		sc->frozen = 1;
	}
}