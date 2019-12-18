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
struct adb_kbd_softc {int /*<<< orphan*/  sc_repeater; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_DEACTIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
akbd_disable(keyboard_t *kbd) 
{
	struct adb_kbd_softc *sc;
	sc = (struct adb_kbd_softc *)(kbd);

	callout_stop(&sc->sc_repeater);
	KBD_DEACTIVATE(kbd);
	return (0);
}