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
struct gpiokeys_softc {int sc_total_keys; int /*<<< orphan*/ * sc_keys; } ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_LOCK_DESTROY (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  KBD_DRIVER_NAME ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 struct gpiokeys_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiokeys_detach_key (struct gpiokeys_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbd_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbd_find_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kbd_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gpiokeys_detach(device_t dev)
{
	struct gpiokeys_softc *sc;
	keyboard_t *kbd;
	int i;

	sc = device_get_softc(dev);

	for (i = 0; i < sc->sc_total_keys; i++)
		gpiokeys_detach_key(sc, &sc->sc_keys[i]);

	kbd = kbd_get_keyboard(kbd_find_keyboard(KBD_DRIVER_NAME,
	    device_get_unit(dev)));

#ifdef KBD_INSTALL_CDEV
	kbd_detach(kbd);
#endif
	kbd_unregister(kbd);

	GPIOKEYS_LOCK_DESTROY(sc);
	if (sc->sc_keys)
		free(sc->sc_keys, M_DEVBUF);

	return (0);
}