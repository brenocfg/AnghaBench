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
struct intr_irqsrc {int dummy; } ;
struct bcm_gpio_softc {int dummy; } ;
struct bcm_gpio_irqsrc {int /*<<< orphan*/  bgi_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_gpio_isrc_unmask (struct bcm_gpio_softc*,struct bcm_gpio_irqsrc*) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_gpio_pic_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct bcm_gpio_softc *sc = device_get_softc(dev);
	struct bcm_gpio_irqsrc *bgi = (struct bcm_gpio_irqsrc *)isrc;

	arm_irq_memory_barrier(bgi->bgi_irq);
	bcm_gpio_isrc_unmask(sc, bgi);
}