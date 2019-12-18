#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {size_t* keycode; int modifiers; } ;
struct TYPE_4__ {int kb_delay1; int kb_delay2; } ;
struct ukbd_softc {int sc_time_ms; int* sc_ntime; int* sc_otime; int sc_delay; TYPE_2__ sc_ndata; TYPE_2__ sc_odata; TYPE_1__ sc_kbd; int /*<<< orphan*/  sc_co_basetime; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int mask; size_t key; } ;

/* Variables and functions */
 size_t KEY_ERROR ; 
 size_t KEY_PRESS ; 
 size_t KEY_RELEASE ; 
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 size_t UKBD_NKEYCODE ; 
 size_t UKBD_NMOD ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  sbinuptime () ; 
 int /*<<< orphan*/  ukbd_event_keyinput (struct ukbd_softc*) ; 
 TYPE_3__* ukbd_mods ; 
 int /*<<< orphan*/  ukbd_put_key (struct ukbd_softc*,size_t) ; 
 int /*<<< orphan*/  ukbd_start_timer (struct ukbd_softc*) ; 

__attribute__((used)) static void
ukbd_interrupt(struct ukbd_softc *sc)
{
	uint32_t n_mod;
	uint32_t o_mod;
	uint32_t now = sc->sc_time_ms;
	int32_t dtime;
	uint8_t key;
	uint8_t i;
	uint8_t j;

	UKBD_LOCK_ASSERT();

	if (sc->sc_ndata.keycode[0] == KEY_ERROR)
		return;

	n_mod = sc->sc_ndata.modifiers;
	o_mod = sc->sc_odata.modifiers;
	if (n_mod != o_mod) {
		for (i = 0; i < UKBD_NMOD; i++) {
			if ((n_mod & ukbd_mods[i].mask) !=
			    (o_mod & ukbd_mods[i].mask)) {
				ukbd_put_key(sc, ukbd_mods[i].key |
				    ((n_mod & ukbd_mods[i].mask) ?
				    KEY_PRESS : KEY_RELEASE));
			}
		}
	}
	/* Check for released keys. */
	for (i = 0; i < UKBD_NKEYCODE; i++) {
		key = sc->sc_odata.keycode[i];
		if (key == 0) {
			continue;
		}
		for (j = 0; j < UKBD_NKEYCODE; j++) {
			if (sc->sc_ndata.keycode[j] == 0) {
				continue;
			}
			if (key == sc->sc_ndata.keycode[j]) {
				goto rfound;
			}
		}
		ukbd_put_key(sc, key | KEY_RELEASE);
rfound:	;
	}

	/* Check for pressed keys. */
	for (i = 0; i < UKBD_NKEYCODE; i++) {
		key = sc->sc_ndata.keycode[i];
		if (key == 0) {
			continue;
		}
		sc->sc_ntime[i] = now + sc->sc_kbd.kb_delay1;
		for (j = 0; j < UKBD_NKEYCODE; j++) {
			if (sc->sc_odata.keycode[j] == 0) {
				continue;
			}
			if (key == sc->sc_odata.keycode[j]) {

				/* key is still pressed */

				sc->sc_ntime[i] = sc->sc_otime[j];
				dtime = (sc->sc_otime[j] - now);

				if (dtime > 0) {
					/* time has not elapsed */
					goto pfound;
				}
				sc->sc_ntime[i] = now + sc->sc_kbd.kb_delay2;
				break;
			}
		}
		if (j == UKBD_NKEYCODE) {
			/* New key - set initial delay and [re]start timer */
			sc->sc_co_basetime = sbinuptime();
			sc->sc_delay = sc->sc_kbd.kb_delay1;
			ukbd_start_timer(sc);
		}
		ukbd_put_key(sc, key | KEY_PRESS);

		/*
                 * If any other key is presently down, force its repeat to be
                 * well in the future (100s).  This makes the last key to be
                 * pressed do the autorepeat.
                 */
		for (j = 0; j != UKBD_NKEYCODE; j++) {
			if (j != i)
				sc->sc_ntime[j] = now + (100 * 1000);
		}
pfound:	;
	}

	sc->sc_odata = sc->sc_ndata;

	memcpy(sc->sc_otime, sc->sc_ntime, sizeof(sc->sc_otime));

	ukbd_event_keyinput(sc);
}