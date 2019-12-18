#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  modifiers; } ;
struct ukbd_softc {int* sc_buffered_char; TYPE_1__ sc_ndata; } ;
struct TYPE_6__ {int /*<<< orphan*/  kb_count; struct ukbd_softc* kb_data; } ;
typedef  TYPE_2__ keyboard_t ;
typedef  int int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_2__*) ; 
 int KEY_RELEASE ; 
 int NN ; 
 int SCAN_PREFIX ; 
 int SCAN_PREFIX_E0 ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 int ukbd_atkeycode (int,int /*<<< orphan*/ ) ; 
 int ukbd_get_key (struct ukbd_softc*,int) ; 
 int ukbd_key2scan (struct ukbd_softc*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ukbd_read(keyboard_t *kbd, int wait)
{
	struct ukbd_softc *sc = kbd->kb_data;
	int32_t usbcode;
#ifdef UKBD_EMULATE_ATSCANCODE
	uint32_t keycode;
	uint32_t scancode;

#endif

	UKBD_LOCK_ASSERT();

	if (!KBD_IS_ACTIVE(kbd))
		return (-1);

#ifdef UKBD_EMULATE_ATSCANCODE
	if (sc->sc_buffered_char[0]) {
		scancode = sc->sc_buffered_char[0];
		if (scancode & SCAN_PREFIX) {
			sc->sc_buffered_char[0] &= ~SCAN_PREFIX;
			return ((scancode & SCAN_PREFIX_E0) ? 0xe0 : 0xe1);
		}
		sc->sc_buffered_char[0] = sc->sc_buffered_char[1];
		sc->sc_buffered_char[1] = 0;
		return (scancode);
	}
#endif					/* UKBD_EMULATE_ATSCANCODE */

	/* XXX */
	usbcode = ukbd_get_key(sc, (wait == FALSE) ? 0 : 1);
	if (!KBD_IS_ACTIVE(kbd) || (usbcode == -1))
		return (-1);

	++(kbd->kb_count);

#ifdef UKBD_EMULATE_ATSCANCODE
	keycode = ukbd_atkeycode(usbcode, sc->sc_ndata.modifiers);
	if (keycode == NN) {
		return -1;
	}
	return (ukbd_key2scan(sc, keycode, sc->sc_ndata.modifiers,
	    (usbcode & KEY_RELEASE)));
#else					/* !UKBD_EMULATE_ATSCANCODE */
	return (usbcode);
#endif					/* UKBD_EMULATE_ATSCANCODE */
}