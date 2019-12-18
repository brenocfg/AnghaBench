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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPPUD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPPUDCLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK_ASSERT (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_WRITE (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_gpio_set_pud(struct bcm_gpio_softc *sc, uint32_t pin, uint32_t state)
{
	uint32_t bank;

	/* Must be called with lock held. */
	BCM_GPIO_LOCK_ASSERT(sc);

	bank = BCM_GPIO_BANK(pin);
	BCM_GPIO_WRITE(sc, BCM_GPIO_GPPUD(0), state);
	BCM_GPIO_WRITE(sc, BCM_GPIO_GPPUDCLK(bank), BCM_GPIO_MASK(pin));
	BCM_GPIO_WRITE(sc, BCM_GPIO_GPPUD(0), 0);
	BCM_GPIO_WRITE(sc, BCM_GPIO_GPPUDCLK(bank), 0);
}