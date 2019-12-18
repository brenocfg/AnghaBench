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
struct mv_gpio_pindev {int member_1; int pin; int /*<<< orphan*/  dev; int /*<<< orphan*/  member_0; } ;
struct callout {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBOUNCE_CHECK_TICKS ; 
 int /*<<< orphan*/  MV_GPIO_ASSERT_LOCKED () ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ callout_active (struct callout*) ; 
 scalar_t__ callout_pending (struct callout*) ; 
 int /*<<< orphan*/  callout_reset (struct callout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mv_gpio_pindev*) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_debounce ; 
 int /*<<< orphan*/  mv_gpio_int_ack (struct mv_gpio_pindev*) ; 

__attribute__((used)) static void
mv_gpio_debounce_start(device_t dev, int pin)
{
	struct callout *c;
	struct mv_gpio_pindev s = {dev, pin};
	struct mv_gpio_pindev *sd;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_ASSERT_LOCKED();

	c = sc->debounce_callouts[pin];
	if (c == NULL) {
		mv_gpio_int_ack(&s);
		return;
	}

	if (callout_pending(c) || callout_active(c)) {
		mv_gpio_int_ack(&s);
		return;
	}

	sd = (struct mv_gpio_pindev *)malloc(sizeof(struct mv_gpio_pindev),
	    M_DEVBUF, M_WAITOK);
	if (sd == NULL) {
		mv_gpio_int_ack(&s);
		return;
	}
	sd->pin = pin;
	sd->dev = dev;

	callout_reset(c, DEBOUNCE_CHECK_TICKS, mv_gpio_debounce, sd);
}