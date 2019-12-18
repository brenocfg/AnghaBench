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
struct bcm_gpio_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_gpio_isrc_eoi (struct bcm_gpio_softc*,struct bcm_gpio_irqsrc*) ; 
 scalar_t__ bcm_gpio_isrc_is_level (struct bcm_gpio_irqsrc*) ; 
 int /*<<< orphan*/  bcm_gpio_isrc_mask (struct bcm_gpio_softc*,struct bcm_gpio_irqsrc*) ; 
 struct bcm_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_gpio_pic_pre_ithread(device_t dev, struct intr_irqsrc *isrc)
{
	struct bcm_gpio_softc *sc = device_get_softc(dev);
	struct bcm_gpio_irqsrc *bgi = (struct bcm_gpio_irqsrc *)isrc;

	bcm_gpio_isrc_mask(sc, bgi);
	if (bcm_gpio_isrc_is_level(bgi))
		bcm_gpio_isrc_eoi(sc, bgi);
}