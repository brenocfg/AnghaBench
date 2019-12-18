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
struct epic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIC_FW_LED_WRITE (struct epic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPIC_LED_POWER_MASK ; 
 int /*<<< orphan*/  EPIC_LED_POWER_OFF ; 
 int /*<<< orphan*/  EPIC_LED_POWER_ON ; 
 int /*<<< orphan*/  EPIC_LED_STATE0 ; 
 int /*<<< orphan*/  EPIC_LOCK (struct epic_softc*) ; 
 int /*<<< orphan*/  EPIC_UNLOCK (struct epic_softc*) ; 

__attribute__((used)) static void
epic_led_power(void *arg, int onoff)
{
	struct epic_softc *sc;

	sc = (struct epic_softc *)arg;

	EPIC_LOCK(sc);
	EPIC_FW_LED_WRITE(sc, EPIC_LED_STATE0, EPIC_LED_POWER_MASK,
	    onoff ? EPIC_LED_POWER_ON : EPIC_LED_POWER_OFF);
	EPIC_UNLOCK(sc);
}