#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int unit; int flags; int keyboard; int adapter; int /*<<< orphan*/  mouse_char; int /*<<< orphan*/  cursor_char; } ;
typedef  TYPE_1__ sc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  SC_CURSOR_CHAR ; 
 int SC_INIT_DONE ; 
 int /*<<< orphan*/  SC_MOUSE_CHAR ; 
 TYPE_1__* sc_softcs ; 

sc_softc_t *
sc_get_softc(int unit, int flags)
{
	sc_softc_t *sc;

	if (unit < 0)
		return (NULL);
	sc = &sc_softcs[unit];
	sc->unit = unit;
	if ((sc->flags & SC_INIT_DONE) == 0) {
		sc->keyboard = -1;
		sc->adapter = -1;
		sc->cursor_char = SC_CURSOR_CHAR;
		sc->mouse_char = SC_MOUSE_CHAR;
	}
	return (sc);
}