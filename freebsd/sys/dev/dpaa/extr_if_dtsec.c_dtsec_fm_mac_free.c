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
struct dtsec_softc {int /*<<< orphan*/ * sc_mach; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_MAC_Disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MAC_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_COMM_MODE_RX_AND_TX ; 

__attribute__((used)) static void
dtsec_fm_mac_free(struct dtsec_softc *sc)
{
	if (sc->sc_mach == NULL)
		return;

	FM_MAC_Disable(sc->sc_mach, e_COMM_MODE_RX_AND_TX);
	FM_MAC_Free(sc->sc_mach);
	sc->sc_mach = NULL;
}