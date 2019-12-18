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
struct ukbd_softc {int sc_flags; scalar_t__ sc_inputs; scalar_t__* sc_buffered_char; } ;
struct TYPE_4__ {struct ukbd_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int UKBD_FLAG_POLLING ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  ukbd_do_poll (struct ukbd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ukbd_check(keyboard_t *kbd)
{
	struct ukbd_softc *sc = kbd->kb_data;

	UKBD_LOCK_ASSERT();

	if (!KBD_IS_ACTIVE(kbd))
		return (0);

	if (sc->sc_flags & UKBD_FLAG_POLLING)
		ukbd_do_poll(sc, 0);

#ifdef UKBD_EMULATE_ATSCANCODE
	if (sc->sc_buffered_char[0]) {
		return (1);
	}
#endif
	if (sc->sc_inputs > 0) {
		return (1);
	}
	return (0);
}