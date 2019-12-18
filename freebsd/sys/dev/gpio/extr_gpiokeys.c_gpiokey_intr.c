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
struct gpiokey {int debounce_interval; int /*<<< orphan*/  debounce_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEY_LOCK (struct gpiokey*) ; 
 int /*<<< orphan*/  GPIOKEY_UNLOCK (struct gpiokey*) ; 
 int /*<<< orphan*/  callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct gpiokey*) ; 
 int /*<<< orphan*/  gpiokey_debounced_intr ; 
 int hz ; 

__attribute__((used)) static void
gpiokey_intr(void *arg)
{
	struct gpiokey *key;
	int debounce_ticks;

	key = arg;

	GPIOKEY_LOCK(key);
	debounce_ticks = (hz * key->debounce_interval) / 1000;
	if (debounce_ticks == 0)
		debounce_ticks = 1;
	if (!callout_pending(&key->debounce_callout))
		callout_reset(&key->debounce_callout, debounce_ticks,
		    gpiokey_debounced_intr, key);
	GPIOKEY_UNLOCK(key);
}