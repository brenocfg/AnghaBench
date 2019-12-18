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
struct gpiokey {scalar_t__ keycode; int /*<<< orphan*/  repeat; int /*<<< orphan*/  repeat_callout; int /*<<< orphan*/  parent_sc; } ;

/* Variables and functions */
 scalar_t__ GPIOKEY_NONE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct gpiokey*) ; 
 int /*<<< orphan*/  gpiokeys_key_event (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
gpiokey_autorepeat(void *arg)
{
	struct gpiokey *key;

	key = arg;

	if (key->keycode == GPIOKEY_NONE)
		return;

	gpiokeys_key_event(key->parent_sc, key->keycode, 1);

	callout_reset(&key->repeat_callout, key->repeat,
		    gpiokey_autorepeat, key);
}