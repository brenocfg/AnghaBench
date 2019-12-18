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
struct gpiokeys_softc {int dummy; } ;
struct TYPE_4__ {struct gpiokeys_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_LOCK (struct gpiokeys_softc*) ; 
 int /*<<< orphan*/  GPIOKEYS_UNLOCK (struct gpiokeys_softc*) ; 
 int gpiokeys_check_char_locked (TYPE_1__*) ; 

__attribute__((used)) static int
gpiokeys_check_char(keyboard_t *kbd)
{
	int result;
	struct gpiokeys_softc *sc = kbd->kb_data;

	GPIOKEYS_LOCK(sc);
	result = gpiokeys_check_char_locked(kbd);
	GPIOKEYS_UNLOCK(sc);

	return (result);
}