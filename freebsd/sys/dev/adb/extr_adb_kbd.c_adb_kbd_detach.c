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
struct adb_kbd_softc {int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_repeater; } ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_DRIVER_NAME ; 
 int /*<<< orphan*/  adb_set_autopoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 struct adb_kbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbd_find_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kbd_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdd_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kbdd_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
adb_kbd_detach(device_t dev) 
{
	struct adb_kbd_softc *sc;
	keyboard_t *kbd;

	sc = device_get_softc(dev);

	adb_set_autopoll(dev,0);
	callout_stop(&sc->sc_repeater);

	mtx_lock(&sc->sc_mutex);

	kbd = kbd_get_keyboard(kbd_find_keyboard(KBD_DRIVER_NAME,
	          device_get_unit(dev)));

	kbdd_disable(kbd);

#ifdef KBD_INSTALL_CDEV
	kbd_detach(kbd);
#endif

	kbdd_term(kbd);

	mtx_unlock(&sc->sc_mutex);

	mtx_destroy(&sc->sc_mutex);
	cv_destroy(&sc->sc_cv);

	return (0);
}