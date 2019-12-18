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
struct terasic_de4led_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERASIC_DE4LED_LOCK (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_SETLED (struct terasic_de4led_softc*,int,int) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_UNLOCK (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  terasic_de4led_update (struct terasic_de4led_softc*) ; 

__attribute__((used)) static void
led_update(struct terasic_de4led_softc *sc, int bit, int onoff)
{

	TERASIC_DE4LED_LOCK(sc);
	TERASIC_DE4LED_SETLED(sc, bit, onoff);
	terasic_de4led_update(sc);
	TERASIC_DE4LED_UNLOCK(sc);
}