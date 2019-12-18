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
struct bwn_softc {int /*<<< orphan*/  sc_led_blink_offdur; int /*<<< orphan*/  sc_led_blink_ch; int /*<<< orphan*/  sc_blink_led; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_GPIO_CONTROL ; 
 int /*<<< orphan*/  BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_led_blink_end ; 
 int /*<<< orphan*/  bwn_led_onoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_led_blink_next(void *arg)
{
	struct bwn_mac *mac = arg;
	struct bwn_softc *sc = mac->mac_sc;
	uint16_t val;

	val = BWN_READ_2(mac, BWN_GPIO_CONTROL);
	val = bwn_led_onoff(sc->sc_blink_led, val, 0);
	BWN_WRITE_2(mac, BWN_GPIO_CONTROL, val);

	callout_reset(&sc->sc_led_blink_ch, sc->sc_led_blink_offdur,
	    bwn_led_blink_end, mac);
}