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
typedef  int uint32_t ;
struct bcm_gpio_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_GPFSEL (int) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK_ASSERT (struct bcm_gpio_softc*) ; 
 int BCM_GPIO_READ (struct bcm_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_WRITE (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bcm_gpio_set_function(struct bcm_gpio_softc *sc, uint32_t pin, uint32_t f)
{
	uint32_t bank, data, offset;

	/* Must be called with lock held. */
	BCM_GPIO_LOCK_ASSERT(sc);

	/* Five banks, 10 pins per bank, 3 bits per pin. */
	bank = pin / 10;
	offset = (pin - bank * 10) * 3;

	data = BCM_GPIO_READ(sc, BCM_GPIO_GPFSEL(bank));
	data &= ~(7 << offset);
	data |= (f << offset);
	BCM_GPIO_WRITE(sc, BCM_GPIO_GPFSEL(bank), data);
}