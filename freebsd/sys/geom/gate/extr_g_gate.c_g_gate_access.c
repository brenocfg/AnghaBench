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
struct g_provider {TYPE_1__* geom; } ;
struct g_gate_softc {int sc_flags; } ;
struct TYPE_2__ {struct g_gate_softc* softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int EPERM ; 
 int G_GATE_FLAG_DESTROY ; 
 int G_GATE_FLAG_READONLY ; 
 int G_GATE_FLAG_WRITEONLY ; 

__attribute__((used)) static int
g_gate_access(struct g_provider *pp, int dr, int dw, int de)
{
	struct g_gate_softc *sc;

	if (dr <= 0 && dw <= 0 && de <= 0)
		return (0);
	sc = pp->geom->softc;
	if (sc == NULL || (sc->sc_flags & G_GATE_FLAG_DESTROY) != 0)
		return (ENXIO);
	/* XXX: Hack to allow read-only mounts. */
#if 0
	if ((sc->sc_flags & G_GATE_FLAG_READONLY) != 0 && dw > 0)
		return (EPERM);
#endif
	if ((sc->sc_flags & G_GATE_FLAG_WRITEONLY) != 0 && dr > 0)
		return (EPERM);
	return (0);
}