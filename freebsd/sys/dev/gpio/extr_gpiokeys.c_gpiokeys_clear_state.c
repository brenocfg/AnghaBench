#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpiokeys_softc {scalar_t__ sc_accents; int /*<<< orphan*/  sc_state; int /*<<< orphan*/  sc_flags; } ;
struct TYPE_3__ {struct gpiokeys_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_GLOBAL_FLAG_POLLING ; 
 int /*<<< orphan*/  LOCK_MASK ; 

__attribute__((used)) static void
gpiokeys_clear_state(keyboard_t *kbd)
{
	struct gpiokeys_softc *sc = kbd->kb_data;

	sc->sc_flags &= ~(GPIOKEYS_GLOBAL_FLAG_POLLING);
	sc->sc_state &= LOCK_MASK;	/* preserve locking key state */
	sc->sc_accents = 0;
}