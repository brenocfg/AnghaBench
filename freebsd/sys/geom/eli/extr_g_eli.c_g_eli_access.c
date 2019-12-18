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
struct g_provider {scalar_t__ acr; scalar_t__ acw; scalar_t__ ace; struct g_geom* geom; } ;
struct g_geom {struct g_eli_softc* softc; } ;
struct g_eli_softc {int sc_flags; } ;

/* Variables and functions */
 int EROFS ; 
 int G_ELI_FLAG_RO ; 
 int G_ELI_FLAG_RW_DETACH ; 
 int G_ELI_FLAG_WOPEN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  g_eli_last_close ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct g_geom*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
g_eli_access(struct g_provider *pp, int dr, int dw, int de)
{
	struct g_eli_softc *sc;
	struct g_geom *gp;

	gp = pp->geom;
	sc = gp->softc;

	if (dw > 0) {
		if (sc->sc_flags & G_ELI_FLAG_RO) {
			/* Deny write attempts. */
			return (EROFS);
		}
		/* Someone is opening us for write, we need to remember that. */
		sc->sc_flags |= G_ELI_FLAG_WOPEN;
		return (0);
	}
	/* Is this the last close? */
	if (pp->acr + dr > 0 || pp->acw + dw > 0 || pp->ace + de > 0)
		return (0);

	/*
	 * Automatically detach on last close if requested.
	 */
	if ((sc->sc_flags & G_ELI_FLAG_RW_DETACH) ||
	    (sc->sc_flags & G_ELI_FLAG_WOPEN)) {
		g_post_event(g_eli_last_close, gp, M_WAITOK, NULL);
	}
	return (0);
}