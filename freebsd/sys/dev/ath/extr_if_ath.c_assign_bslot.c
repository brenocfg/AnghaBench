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
typedef  size_t u_int ;
struct ath_softc {int /*<<< orphan*/ ** sc_bslot; } ;

/* Variables and functions */
 size_t ATH_BCBUF ; 

__attribute__((used)) static int
assign_bslot(struct ath_softc *sc)
{
	u_int slot, free;

	free = 0;
	for (slot = 0; slot < ATH_BCBUF; slot++)
		if (sc->sc_bslot[slot] == NULL) {
			if (sc->sc_bslot[(slot+1)%ATH_BCBUF] == NULL &&
			    sc->sc_bslot[(slot-1)%ATH_BCBUF] == NULL)
				return slot;
			free = slot;
			/* NB: keep looking for a double slot */
		}
	return free;
}