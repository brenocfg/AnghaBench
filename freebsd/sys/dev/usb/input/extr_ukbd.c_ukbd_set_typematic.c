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
struct ukbd_softc {int /*<<< orphan*/ * sc_evdev; } ;
struct TYPE_4__ {int kb_delay1; int kb_delay2; struct ukbd_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  evdev_push_repeats (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
ukbd_set_typematic(keyboard_t *kbd, int code)
{
#ifdef EVDEV_SUPPORT
	struct ukbd_softc *sc = kbd->kb_data;
#endif
	static const int delays[] = {250, 500, 750, 1000};
	static const int rates[] = {34, 38, 42, 46, 50, 55, 59, 63,
		68, 76, 84, 92, 100, 110, 118, 126,
		136, 152, 168, 184, 200, 220, 236, 252,
	272, 304, 336, 368, 400, 440, 472, 504};

	if (code & ~0x7f) {
		return (EINVAL);
	}
	kbd->kb_delay1 = delays[(code >> 5) & 3];
	kbd->kb_delay2 = rates[code & 0x1f];
#ifdef EVDEV_SUPPORT
	if (sc->sc_evdev != NULL)
		evdev_push_repeats(sc->sc_evdev, kbd);
#endif
	return (0);
}