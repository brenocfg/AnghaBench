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
struct g_gate_softc {int /*<<< orphan*/  sc_ref; TYPE_1__* sc_provider; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int G_GATE_NAME_GIVEN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int g_gate_maxunits ; 
 struct g_gate_softc** g_gate_units ; 
 int /*<<< orphan*/  g_gate_units_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct g_gate_softc *
g_gate_hold(int unit, const char *name)
{
	struct g_gate_softc *sc = NULL;

	mtx_lock(&g_gate_units_lock);
	if (unit >= 0 && unit < g_gate_maxunits)
		sc = g_gate_units[unit];
	else if (unit == G_GATE_NAME_GIVEN) {
		KASSERT(name != NULL, ("name is NULL"));
		for (unit = 0; unit < g_gate_maxunits; unit++) {
			if (g_gate_units[unit] == NULL)
				continue;
			if (strcmp(name,
			    g_gate_units[unit]->sc_provider->name) != 0) {
				continue;
			}
			sc = g_gate_units[unit];
			break;
		}
	}
	if (sc != NULL)
		sc->sc_ref++;
	mtx_unlock(&g_gate_units_lock);
	return (sc);
}