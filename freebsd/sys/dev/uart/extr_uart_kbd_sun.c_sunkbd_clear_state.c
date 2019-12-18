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
struct sunkbd_softc {int sc_repeat_key; scalar_t__* sc_buffered_char; int /*<<< orphan*/  sc_state; scalar_t__ sc_repeating; scalar_t__ sc_polling; scalar_t__ sc_flags; scalar_t__ sc_composed_char; scalar_t__ sc_accents; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_MASK ; 

__attribute__((used)) static void
sunkbd_clear_state(keyboard_t *kbd)
{
	struct sunkbd_softc *sc;

	sc = (struct sunkbd_softc *)kbd;
	sc->sc_repeat_key = -1;
	sc->sc_accents = 0;
	sc->sc_composed_char = 0;
	sc->sc_flags = 0;
	sc->sc_polling = 0;
	sc->sc_repeating = 0;
	sc->sc_state &= LOCK_MASK;	/* Preserve locking key state. */

#if defined(SUNKBD_EMULATE_ATKBD)
	sc->sc_buffered_char[0] = 0;
	sc->sc_buffered_char[1] = 0;
#endif
}