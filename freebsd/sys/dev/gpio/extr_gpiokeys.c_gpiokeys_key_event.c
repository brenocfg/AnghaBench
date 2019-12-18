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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct gpiokeys_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_LOCK (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  GPIOKEYS_UNLOCK (struct gpiokeys_softc*) ; 
 int KEY_RELEASE ; 
 int SCAN_KEYCODE_MASK ; 
 int SCAN_PREFIX_E0 ; 
 int SCAN_PREFIX_E1 ; 
 int /*<<< orphan*/  gpiokeys_event_keyinput (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  gpiokeys_put_key (struct gpiokeys_softc*,int) ; 

__attribute__((used)) static void
gpiokeys_key_event(struct gpiokeys_softc *sc, uint16_t keycode, int pressed)
{
	uint32_t key;


	key = keycode & SCAN_KEYCODE_MASK;

	if (!pressed)
		key |= KEY_RELEASE;

	GPIOKEYS_LOCK(sc);
	if (keycode & SCAN_PREFIX_E0)
		gpiokeys_put_key(sc, 0xe0);
	else if (keycode & SCAN_PREFIX_E1)
		gpiokeys_put_key(sc, 0xe1);

	gpiokeys_put_key(sc, key);
	GPIOKEYS_UNLOCK(sc);

	gpiokeys_event_keyinput(sc);
}