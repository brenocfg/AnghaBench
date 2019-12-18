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
struct terasic_de4led_softc {int /*<<< orphan*/  tdl_bits; int /*<<< orphan*/  tdl_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERASIC_DE4LED_LOCK_ASSERT (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_OFF_LED ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
terasic_de4led_update(struct terasic_de4led_softc *sc)
{

	TERASIC_DE4LED_LOCK_ASSERT(sc);

	bus_write_1(sc->tdl_res, TERASIC_DE4LED_OFF_LED, sc->tdl_bits);
}