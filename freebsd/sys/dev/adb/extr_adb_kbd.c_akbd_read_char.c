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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
struct adb_kbd_softc {scalar_t__ sc_mode; int* at_buffered_char; int buffers; int* buffer; int /*<<< orphan*/  sc_mutex; int /*<<< orphan*/  sc_cv; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 scalar_t__ K_CODE ; 
 scalar_t__ K_RAW ; 
 int NOKEY ; 
 int SCAN_PREFIX ; 
 int SCAN_PREFIX_CTL ; 
 int SCAN_PREFIX_E0 ; 
 int SCAN_PREFIX_SHIFT ; 
 int SCAN_RELEASE ; 
 int* adb_to_at_scancode_map ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int keycode2scancode (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int 
akbd_read_char(keyboard_t *kbd, int wait) 
{
	struct adb_kbd_softc *sc;
	uint16_t key;
	uint8_t adb_code;
	int i;

	sc = (struct adb_kbd_softc *)(kbd);

	mtx_lock(&sc->sc_mutex);

#if defined(AKBD_EMULATE_ATKBD)
	if (sc->sc_mode == K_RAW && sc->at_buffered_char[0]) {
		key = sc->at_buffered_char[0];
		if (key & SCAN_PREFIX) {
			sc->at_buffered_char[0] = key & ~SCAN_PREFIX;
			key = (key & SCAN_PREFIX_E0) ? 0xe0 : 0xe1;
		} else {
			sc->at_buffered_char[0] = sc->at_buffered_char[1];
			sc->at_buffered_char[1] = 0;
		}

		mtx_unlock(&sc->sc_mutex);

		return (key);
	}
#endif

	if (!sc->buffers && wait)
		cv_wait(&sc->sc_cv,&sc->sc_mutex);

	if (!sc->buffers) {
		mtx_unlock(&sc->sc_mutex);
		return (NOKEY);
	}

	adb_code = sc->buffer[0];

	for (i = 1; i < sc->buffers; i++)
		sc->buffer[i-1] = sc->buffer[i];

	sc->buffers--;

	#ifdef AKBD_EMULATE_ATKBD
		key = adb_to_at_scancode_map[adb_code & 0x7f];
		if (sc->sc_mode == K_CODE) {
			/* Add the key-release bit */
			key |= adb_code & 0x80;
		} else if (sc->sc_mode == K_RAW) {
			/*
			 * In the raw case, we have to emulate the gross
			 * variable-length AT keyboard thing. Since this code
			 * is copied from sunkbd, which is the same code
			 * as ukbd, it might be nice to have this centralized.
			 */

			key = keycode2scancode(key, 
			    0, adb_code & 0x80);

			if (key & SCAN_PREFIX) {
				if (key & SCAN_PREFIX_CTL) {
					sc->at_buffered_char[0] =
					    0x1d | (key & SCAN_RELEASE);
					sc->at_buffered_char[1] =
					    key & ~SCAN_PREFIX;
				} else if (key & SCAN_PREFIX_SHIFT) {
					sc->at_buffered_char[0] =
					    0x2a | (key & SCAN_RELEASE);
					sc->at_buffered_char[1] =
					    key & ~SCAN_PREFIX_SHIFT;
				} else {
					sc->at_buffered_char[0] =
					    key & ~SCAN_PREFIX;
					sc->at_buffered_char[1] = 0;
				}
	
				key = (key & SCAN_PREFIX_E0) ? 0xe0 : 0xe1;
			}
		}
	#else
		key = adb_code;
	#endif

	mtx_unlock(&sc->sc_mutex);

	return (key);
}