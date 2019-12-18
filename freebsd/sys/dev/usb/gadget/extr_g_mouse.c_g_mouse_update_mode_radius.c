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
struct g_mouse_softc {int sc_radius; int /*<<< orphan*/  sc_mode; } ;

/* Variables and functions */
 int g_mouse_cursor_radius ; 
 int /*<<< orphan*/  g_mouse_mode ; 

__attribute__((used)) static void
g_mouse_update_mode_radius(struct g_mouse_softc *sc)
{
	sc->sc_mode = g_mouse_mode;
	sc->sc_radius = g_mouse_cursor_radius;

	if (sc->sc_radius < 0)
		sc->sc_radius = 0;
	else if (sc->sc_radius > 1023)
		sc->sc_radius = 1023;
}