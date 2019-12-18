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
typedef  scalar_t__ uint32_t ;
struct bcm_gpio_softc {int dummy; } ;
struct bcm_gpio_irqsrc {scalar_t__ bgi_mode; int /*<<< orphan*/  bgi_mask; int /*<<< orphan*/  bgi_irq; } ;

/* Variables and functions */
 scalar_t__ BCM_GPIO_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPFEN (scalar_t__) ; 
 int /*<<< orphan*/  BCM_GPIO_GPHEN (scalar_t__) ; 
 int /*<<< orphan*/  BCM_GPIO_GPLEN (scalar_t__) ; 
 int /*<<< orphan*/  BCM_GPIO_GPREN (scalar_t__) ; 
 int /*<<< orphan*/  BCM_GPIO_LOCK (struct bcm_gpio_softc*) ; 
 int /*<<< orphan*/  BCM_GPIO_UNLOCK (struct bcm_gpio_softc*) ; 
 scalar_t__ GPIO_INTR_EDGE_BOTH ; 
 scalar_t__ GPIO_INTR_EDGE_FALLING ; 
 scalar_t__ GPIO_INTR_EDGE_RISING ; 
 scalar_t__ GPIO_INTR_LEVEL_HIGH ; 
 scalar_t__ GPIO_INTR_LEVEL_LOW ; 
 int /*<<< orphan*/  bcm_gpio_modify (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bcm_gpio_pic_config_intr(struct bcm_gpio_softc *sc, struct bcm_gpio_irqsrc *bgi,
    uint32_t mode)
{
	uint32_t bank;

	bank = BCM_GPIO_BANK(bgi->bgi_irq);
	BCM_GPIO_LOCK(sc);
	bcm_gpio_modify(sc, BCM_GPIO_GPREN(bank), bgi->bgi_mask,
	    mode == GPIO_INTR_EDGE_RISING || mode == GPIO_INTR_EDGE_BOTH);
	bcm_gpio_modify(sc, BCM_GPIO_GPFEN(bank), bgi->bgi_mask,
	    mode == GPIO_INTR_EDGE_FALLING || mode == GPIO_INTR_EDGE_BOTH);
	bcm_gpio_modify(sc, BCM_GPIO_GPHEN(bank), bgi->bgi_mask,
	    mode == GPIO_INTR_LEVEL_HIGH);
	bcm_gpio_modify(sc, BCM_GPIO_GPLEN(bank), bgi->bgi_mask,
	    mode == GPIO_INTR_LEVEL_LOW);
	bgi->bgi_mode = mode;
	BCM_GPIO_UNLOCK(sc);
}