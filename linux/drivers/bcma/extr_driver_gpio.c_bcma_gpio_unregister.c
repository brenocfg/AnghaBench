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
struct bcma_drv_cc {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_gpio_irq_exit (struct bcma_drv_cc*) ; 
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 

int bcma_gpio_unregister(struct bcma_drv_cc *cc)
{
	bcma_gpio_irq_exit(cc);
	gpiochip_remove(&cc->gpio);
	return 0;
}