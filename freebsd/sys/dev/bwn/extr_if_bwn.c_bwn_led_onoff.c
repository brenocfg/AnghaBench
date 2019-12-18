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
struct bwn_led {int led_flags; int /*<<< orphan*/  led_mask; } ;

/* Variables and functions */
 int BWN_LED_F_ACTLOW ; 

__attribute__((used)) static __inline uint16_t
bwn_led_onoff(const struct bwn_led *led, uint16_t val, int on)
{

	if (led->led_flags & BWN_LED_F_ACTLOW)
		on = !on;
	if (on)
		val |= led->led_mask;
	else
		val &= ~led->led_mask;
	return val;
}