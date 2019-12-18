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
struct bcm_gpio_irqsrc {int /*<<< orphan*/  bgi_mask; int /*<<< orphan*/  bgi_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_GPIO_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_GPEDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_GPIO_WRITE (struct bcm_gpio_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bcm_gpio_isrc_eoi(struct bcm_gpio_softc *sc, struct bcm_gpio_irqsrc *bgi)
{
	uint32_t bank;

	/* Write 1 to clear. */
	bank = BCM_GPIO_BANK(bgi->bgi_irq);
	BCM_GPIO_WRITE(sc, BCM_GPIO_GPEDS(bank), bgi->bgi_mask);
}