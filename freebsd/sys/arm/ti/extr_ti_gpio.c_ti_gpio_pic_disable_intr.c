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
struct ti_gpio_softc {int dummy; } ;
struct ti_gpio_irqsrc {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ti_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_gpio_isrc_mask (struct ti_gpio_softc*,struct ti_gpio_irqsrc*) ; 

__attribute__((used)) static void
ti_gpio_pic_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct ti_gpio_softc *sc = device_get_softc(dev);
	struct ti_gpio_irqsrc *tgi = (struct ti_gpio_irqsrc *)isrc;

	ti_gpio_isrc_mask(sc, tgi);
}