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
struct rb750_led_dev {int active_low; int /*<<< orphan*/  mask; int /*<<< orphan*/  (* latch_change ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_OFF ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rb750_led_dev* to_rbled (struct led_classdev*) ; 

__attribute__((used)) static void rb750_led_brightness_set(struct led_classdev *led_cdev,
				     enum led_brightness value)
{
	struct rb750_led_dev *rbled = to_rbled(led_cdev);
	int level;

	level = (value == LED_OFF) ? 0 : 1;
	level ^= rbled->active_low;

	if (level)
		rbled->latch_change(0, rbled->mask);
	else
		rbled->latch_change(rbled->mask, 0);
}