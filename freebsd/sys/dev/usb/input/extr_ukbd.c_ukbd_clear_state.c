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
struct ukbd_softc {int sc_flags; int /*<<< orphan*/  sc_otime; int /*<<< orphan*/  sc_ntime; int /*<<< orphan*/  sc_odata; int /*<<< orphan*/  sc_ndata; scalar_t__* sc_buffered_char; scalar_t__ sc_composed_char; scalar_t__ sc_accents; int /*<<< orphan*/  sc_state; } ;
struct TYPE_3__ {struct ukbd_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_MASK ; 
 int UKBD_FLAG_COMPOSE ; 
 int UKBD_FLAG_POLLING ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ukbd_clear_state(keyboard_t *kbd)
{
	struct ukbd_softc *sc = kbd->kb_data;

	UKBD_LOCK_ASSERT();

	sc->sc_flags &= ~(UKBD_FLAG_COMPOSE | UKBD_FLAG_POLLING);
	sc->sc_state &= LOCK_MASK;	/* preserve locking key state */
	sc->sc_accents = 0;
	sc->sc_composed_char = 0;
#ifdef UKBD_EMULATE_ATSCANCODE
	sc->sc_buffered_char[0] = 0;
	sc->sc_buffered_char[1] = 0;
#endif
	memset(&sc->sc_ndata, 0, sizeof(sc->sc_ndata));
	memset(&sc->sc_odata, 0, sizeof(sc->sc_odata));
	memset(&sc->sc_ntime, 0, sizeof(sc->sc_ntime));
	memset(&sc->sc_otime, 0, sizeof(sc->sc_otime));
}