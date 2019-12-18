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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwi_softc {int /*<<< orphan*/  sc_led_blink_offdur; int /*<<< orphan*/  sc_led_blink_ch; int /*<<< orphan*/  sc_blink_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_MAC_GPIO_CTRL ; 
 int /*<<< orphan*/  CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_led_blink_end ; 
 int /*<<< orphan*/  bwi_led_onoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bwi_softc*) ; 

__attribute__((used)) static void
bwi_led_blink_next(void *xsc)
{
	struct bwi_softc *sc = xsc;
	uint16_t val;

	val = CSR_READ_2(sc, BWI_MAC_GPIO_CTRL);
	val = bwi_led_onoff(sc->sc_blink_led, val, 0);
	CSR_WRITE_2(sc, BWI_MAC_GPIO_CTRL, val);

	callout_reset(&sc->sc_led_blink_ch, sc->sc_led_blink_offdur,
	    bwi_led_blink_end, sc);
}