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
struct gpiokey {scalar_t__ keycode; int /*<<< orphan*/  parent_sc; int /*<<< orphan*/  repeat_callout; scalar_t__ autorepeat; int /*<<< orphan*/  repeat_delay; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 scalar_t__ GPIOKEY_NONE ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpiokey*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_pin_is_active (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  gpiokey_autorepeat ; 
 int /*<<< orphan*/  gpiokeys_key_event (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
gpiokey_debounced_intr(void *arg)
{
	struct gpiokey *key;
	bool active;

	key = arg;

	if (key->keycode == GPIOKEY_NONE)
		return;

	gpio_pin_is_active(key->pin, &active);
	if (active) {
		gpiokeys_key_event(key->parent_sc, key->keycode, 1);
		if (key->autorepeat) {
			callout_reset(&key->repeat_callout, key->repeat_delay,
			    gpiokey_autorepeat, key);
		}
	}
	else {
		if (key->autorepeat &&
		    callout_pending(&key->repeat_callout))
			callout_stop(&key->repeat_callout);
		gpiokeys_key_event(key->parent_sc, key->keycode, 0);
	}
}