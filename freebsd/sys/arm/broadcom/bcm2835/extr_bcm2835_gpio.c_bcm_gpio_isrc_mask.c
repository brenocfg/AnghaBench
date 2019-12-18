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
struct bcm_gpio_irqsrc {int bgi_mode; int /*<<< orphan*/  bgi_mask; int /*<<< orphan*/  bgi_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_CLEAR_BITS (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPFEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPHEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_UNLOCK (struct bcm_gpio_softc*) ; 
#define  GPIO_INTR_EDGE_BOTH 132 
#define  GPIO_INTR_EDGE_FALLING 131 
#define  GPIO_INTR_EDGE_RISING 130 
#define  GPIO_INTR_LEVEL_HIGH 129 
#define  GPIO_INTR_LEVEL_LOW 128 

__attribute__((used)) static inline void
bcm_gpio_isrc_mask(struct bcm_gpio_softc *sc, struct bcm_gpio_irqsrc *bgi)
{
	uint32_t bank;

	bank = BCM_GPIO_BANK(bgi->bgi_irq);
	BCM_GPIO_LOCK(sc);
	switch (bgi->bgi_mode) {
	case GPIO_INTR_LEVEL_LOW:
		BCM_GPIO_CLEAR_BITS(sc, BCM_GPIO_GPLEN(bank), bgi->bgi_mask);
		break;
	case GPIO_INTR_LEVEL_HIGH:
		BCM_GPIO_CLEAR_BITS(sc, BCM_GPIO_GPHEN(bank), bgi->bgi_mask);
		break;
	case GPIO_INTR_EDGE_RISING:
		BCM_GPIO_CLEAR_BITS(sc, BCM_GPIO_GPREN(bank), bgi->bgi_mask);
		break;
	case GPIO_INTR_EDGE_FALLING:
		BCM_GPIO_CLEAR_BITS(sc, BCM_GPIO_GPFEN(bank), bgi->bgi_mask);
		break;
	case GPIO_INTR_EDGE_BOTH:
		BCM_GPIO_CLEAR_BITS(sc, BCM_GPIO_GPREN(bank), bgi->bgi_mask);
		BCM_GPIO_CLEAR_BITS(sc, BCM_GPIO_GPFEN(bank), bgi->bgi_mask);
		break;
	}
	BCM_GPIO_UNLOCK(sc);
}