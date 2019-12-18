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
struct mv_gpio_softc {TYPE_1__** gpio_events; } ;
struct intr_irqsrc {TYPE_1__* isrc_event; int /*<<< orphan*/ * isrc_filter; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  ie_handlers; } ;

/* Variables and functions */
 scalar_t__ CK_SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MV_GPIO_ASSERT_LOCKED () ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_isrc_dispatch (struct intr_irqsrc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mv_gpio_intr_handler(device_t dev, int pin)
{
#ifdef INTRNG
	struct intr_irqsrc isrc;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_ASSERT_LOCKED();

#ifdef INTR_SOLO
	isrc.isrc_filter = NULL;
#endif
	isrc.isrc_event = sc->gpio_events[pin];

	if (isrc.isrc_event == NULL ||
	    CK_SLIST_EMPTY(&isrc.isrc_event->ie_handlers))
		return;

	intr_isrc_dispatch(&isrc, NULL);
#endif
}