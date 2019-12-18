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
typedef  int /*<<< orphan*/  uint32_t ;
struct gpiokeys_softc {int dummy; } ;
struct TYPE_4__ {struct gpiokeys_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_LOCK (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  GPIOKEYS_UNLOCK (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  gpiokeys_read_char_locked (TYPE_1__*,int) ; 

__attribute__((used)) static uint32_t
gpiokeys_read_char(keyboard_t *kbd, int wait)
{
	uint32_t keycode;
	struct gpiokeys_softc *sc = kbd->kb_data;

	GPIOKEYS_LOCK(sc);
	keycode = gpiokeys_read_char_locked(kbd, wait);
	GPIOKEYS_UNLOCK(sc);

	return (keycode);
}