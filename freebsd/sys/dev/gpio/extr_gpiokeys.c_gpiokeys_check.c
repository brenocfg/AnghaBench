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
struct gpiokeys_softc {int sc_flags; scalar_t__ sc_inputs; } ;
struct TYPE_4__ {struct gpiokeys_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_ASSERT_LOCKED (struct gpiokeys_softc*) ; 
 int GPIOKEYS_GLOBAL_FLAG_POLLING ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  gpiokeys_do_poll (struct gpiokeys_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpiokeys_check(keyboard_t *kbd)
{
	struct gpiokeys_softc *sc = kbd->kb_data;

	GPIOKEYS_ASSERT_LOCKED(sc);

	if (!KBD_IS_ACTIVE(kbd))
		return (0);

	if (sc->sc_flags & GPIOKEYS_GLOBAL_FLAG_POLLING)
		gpiokeys_do_poll(sc, 0);

	if (sc->sc_inputs > 0) {
		return (1);
	}
	return (0);
}