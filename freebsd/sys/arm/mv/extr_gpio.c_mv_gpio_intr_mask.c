#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mv_gpio_softc {size_t pin_num; TYPE_1__* gpio_setup; } ;
struct mv_gpio_pindev {size_t pin; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int gp_flags; } ;

/* Variables and functions */
 int MV_GPIO_IN_IRQ_DOUBLE_EDGE ; 
 int MV_GPIO_IN_IRQ_EDGE ; 
 int /*<<< orphan*/  MV_GPIO_LOCK () ; 
 int /*<<< orphan*/  MV_GPIO_UNLOCK () ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_edge (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_int_ack (struct mv_gpio_pindev*) ; 
 int /*<<< orphan*/  mv_gpio_level (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv_gpio_intr_mask(struct mv_gpio_pindev *s)
{
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(s->dev);

	if (s->pin >= sc->pin_num)
		return;

	MV_GPIO_LOCK();

	if (sc->gpio_setup[s->pin].gp_flags & (MV_GPIO_IN_IRQ_EDGE |
	    MV_GPIO_IN_IRQ_DOUBLE_EDGE))
		mv_gpio_edge(s->dev, s->pin, 0);
	else
		mv_gpio_level(s->dev, s->pin, 0);

	/*
	 * The interrupt has to be acknowledged before scheduling an interrupt
	 * thread. This way we allow for interrupt source to trigger again
	 * (which can happen with shared IRQs e.g. PCI) while processing the
	 * current event.
	 */
	mv_gpio_int_ack(s);

	MV_GPIO_UNLOCK();

	return;
}