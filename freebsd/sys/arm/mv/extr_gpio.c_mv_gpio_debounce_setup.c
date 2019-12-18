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
struct mv_gpio_softc {struct callout** debounce_callouts; } ;
struct callout {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MV_GPIO_ASSERT_LOCKED () ; 
 scalar_t__ callout_active (struct callout*) ; 
 int /*<<< orphan*/  callout_deactivate (struct callout*) ; 
 int /*<<< orphan*/  callout_stop (struct callout*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_gpio_debounce_setup(device_t dev, int pin)
{
	struct callout *c;
	struct mv_gpio_softc *sc;

	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_ASSERT_LOCKED();

	c = sc->debounce_callouts[pin];
	if (c == NULL)
		return (ENXIO);

	if (callout_active(c))
		callout_deactivate(c);

	callout_stop(c);

	return (0);
}