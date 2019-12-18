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
struct bwi_led {int l_flags; int /*<<< orphan*/  l_mask; } ;

/* Variables and functions */
 int BWI_LED_F_ACTLOW ; 

__attribute__((used)) static __inline uint16_t
bwi_led_onoff(const struct bwi_led *led, uint16_t val, int on)
{
	if (led->l_flags & BWI_LED_F_ACTLOW)
		on = !on;
	if (on)
		val |= led->l_mask;
	else
		val &= ~led->l_mask;
	return val;
}