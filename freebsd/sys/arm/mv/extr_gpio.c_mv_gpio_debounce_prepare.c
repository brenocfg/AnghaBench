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
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  callout_init (struct callout*,int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_gpio_debounce_prepare(device_t dev, int pin)
{
	struct callout *c;
	struct mv_gpio_softc *sc;

	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	c = sc->debounce_callouts[pin];
	if (c == NULL) {
		c = (struct callout *)malloc(sizeof(struct callout),
		    M_DEVBUF, M_WAITOK);
		sc->debounce_callouts[pin] = c;
		if (c == NULL)
			return (ENOMEM);
		callout_init(c, 1);
	}

	return (0);
}