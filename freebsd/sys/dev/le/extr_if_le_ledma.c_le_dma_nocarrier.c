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
struct le_dma_softc {int /*<<< orphan*/  sc_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifm_media; } ;
struct lance_softc {int /*<<< orphan*/  sc_ifp; TYPE_1__ sc_media; } ;

/* Variables and functions */
 int E_TP_AUI ; 
#define  IFM_10_5 130 
#define  IFM_10_T 129 
#define  IFM_AUTO 128 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int L64854_GCSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le_dma_setaui (struct lance_softc*) ; 
 int /*<<< orphan*/  le_dma_setutp (struct lance_softc*) ; 

__attribute__((used)) static void
le_dma_nocarrier(struct lance_softc *sc)
{
	struct le_dma_softc *lesc = (struct le_dma_softc *)sc;

	/*
	 * Check if the user has requested a certain cable type, and
	 * if so, honor that request.
	 */

	if (L64854_GCSR(lesc->sc_dma) & E_TP_AUI) {
		switch (IFM_SUBTYPE(sc->sc_media.ifm_media)) {
		case IFM_10_5:
		case IFM_AUTO:
			if_printf(sc->sc_ifp, "lost carrier on UTP port, "
			    "switching to AUI port\n");
			le_dma_setaui(sc);
		}
	} else {
		switch (IFM_SUBTYPE(sc->sc_media.ifm_media)) {
		case IFM_10_T:
		case IFM_AUTO:
			if_printf(sc->sc_ifp, "lost carrier on AUI port, "
			    "switching to UTP port\n");
			le_dma_setutp(sc);
		}
	}
}