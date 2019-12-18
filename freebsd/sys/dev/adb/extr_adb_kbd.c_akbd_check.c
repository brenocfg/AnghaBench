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
struct adb_kbd_softc {scalar_t__ buffers; int /*<<< orphan*/  sc_mutex; scalar_t__* at_buffered_char; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
akbd_check(keyboard_t *kbd) 
{
	struct adb_kbd_softc *sc;

	if (!KBD_IS_ACTIVE(kbd))
		return (FALSE);

	sc = (struct adb_kbd_softc *)(kbd);

	mtx_lock(&sc->sc_mutex);
#ifdef AKBD_EMULATE_ATKBD
		if (sc->at_buffered_char[0]) {
			mtx_unlock(&sc->sc_mutex);
			return (TRUE);
		}
#endif

		if (sc->buffers > 0) {
			mtx_unlock(&sc->sc_mutex);
			return (TRUE); 
		}
	mtx_unlock(&sc->sc_mutex);

	return (FALSE);
}