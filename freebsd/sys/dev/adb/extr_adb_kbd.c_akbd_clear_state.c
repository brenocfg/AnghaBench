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
struct adb_kbd_softc {int /*<<< orphan*/  sc_mutex; scalar_t__* at_buffered_char; int /*<<< orphan*/  sc_repeater; scalar_t__ buffers; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void akbd_clear_state(keyboard_t *kbd)
{
	struct adb_kbd_softc *sc;

	sc = (struct adb_kbd_softc *)(kbd);

	mtx_lock(&sc->sc_mutex);

	sc->buffers = 0;
	callout_stop(&sc->sc_repeater);

#if defined(AKBD_EMULATE_ATKBD)	
	sc->at_buffered_char[0] = 0;
	sc->at_buffered_char[1] = 0;
#endif
	mtx_unlock(&sc->sc_mutex);
}