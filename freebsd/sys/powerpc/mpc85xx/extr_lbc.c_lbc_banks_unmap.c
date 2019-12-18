#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lbc_softc {TYPE_1__* sc_range; } ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/  addr; int /*<<< orphan*/  kva; } ;

/* Variables and functions */
 int LBC_DEV_MAX ; 
 int /*<<< orphan*/  OCP85XX_TGTIF_LBC ; 
 int /*<<< orphan*/  law_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
lbc_banks_unmap(struct lbc_softc *sc)
{
	int r;

	r = 0;
	while (r < LBC_DEV_MAX) {
		if (sc->sc_range[r].size == 0)
			return;

		pmap_unmapdev(sc->sc_range[r].kva, sc->sc_range[r].size);
		law_disable(OCP85XX_TGTIF_LBC, sc->sc_range[r].addr,
		    sc->sc_range[r].size);
		r++;
	}
}