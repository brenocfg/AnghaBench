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
struct gpiokeys_softc {int /*<<< orphan*/  sc_dev; } ;
struct gpiokey {scalar_t__ pin; int /*<<< orphan*/  debounce_callout; int /*<<< orphan*/  repeat_callout; scalar_t__ irq_res; int /*<<< orphan*/  irq_rid; scalar_t__ intr_hl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEY_LOCK (struct gpiokey*) ; 
 int /*<<< orphan*/  GPIOKEY_LOCK_DESTROY (struct gpiokey*) ; 
 int /*<<< orphan*/  GPIOKEY_UNLOCK (struct gpiokey*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_pin_release (scalar_t__) ; 

__attribute__((used)) static void
gpiokeys_detach_key(struct gpiokeys_softc *sc, struct gpiokey *key)
{

	GPIOKEY_LOCK(key);
	if (key->intr_hl)
		bus_teardown_intr(sc->sc_dev, key->irq_res, key->intr_hl);
	if (key->irq_res)
		bus_release_resource(sc->sc_dev, SYS_RES_IRQ,
		    key->irq_rid, key->irq_res);
	if (callout_pending(&key->repeat_callout))
		callout_drain(&key->repeat_callout);
	if (callout_pending(&key->debounce_callout))
		callout_drain(&key->debounce_callout);
	if (key->pin)
		gpio_pin_release(key->pin);
	GPIOKEY_UNLOCK(key);

	GPIOKEY_LOCK_DESTROY(key);
}