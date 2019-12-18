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
typedef  int uint16_t ;
struct run_softc {int leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT2860_MCU_CMD_LEDS ; 
 int /*<<< orphan*/  run_mcu_cmd (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run_set_leds(struct run_softc *sc, uint16_t which)
{
	(void)run_mcu_cmd(sc, RT2860_MCU_CMD_LEDS,
	    which | (sc->leds & 0x7f));
}