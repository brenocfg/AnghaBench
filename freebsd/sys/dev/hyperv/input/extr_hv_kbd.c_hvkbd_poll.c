#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_5__ {scalar_t__ sc_polling; int /*<<< orphan*/  sc_flags; } ;
typedef  TYPE_2__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  HVKBD_FLAG_POLLING ; 
 int /*<<< orphan*/  HVKBD_LOCK () ; 
 int /*<<< orphan*/  HVKBD_UNLOCK () ; 

__attribute__((used)) static int
hvkbd_poll(keyboard_t *kbd, int on)
{
	hv_kbd_sc *sc = kbd->kb_data;

	HVKBD_LOCK();
	/*
	 * Keep a reference count on polling to allow recursive
	 * cngrab() during a panic for example.
	 */
	if (on)
		sc->sc_polling++;
	else if (sc->sc_polling > 0)
		sc->sc_polling--;

	if (sc->sc_polling != 0) {
		sc->sc_flags |= HVKBD_FLAG_POLLING;
	} else {
		sc->sc_flags &= ~HVKBD_FLAG_POLLING;
	}
	HVKBD_UNLOCK();
	return (0);
}