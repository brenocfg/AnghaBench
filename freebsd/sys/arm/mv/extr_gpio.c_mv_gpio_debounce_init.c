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
typedef  int uint8_t ;
struct mv_gpio_softc {int* debounce_counters; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DEBOUNCE_CHECK_MS ; 
 int DEBOUNCE_HI_LO_MS ; 
 int DEBOUNCE_LO_HI_MS ; 
 int /*<<< orphan*/  MV_GPIO_ASSERT_LOCKED () ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_debounced_state_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mv_gpio_polarity (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_gpio_value_get (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
mv_gpio_debounce_init(device_t dev, int pin)
{
	uint8_t raw_read;
	int *cnt;
	struct mv_gpio_softc *sc;

	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_ASSERT_LOCKED();

	cnt = &sc->debounce_counters[pin];
	raw_read = (mv_gpio_value_get(dev, pin, 1) ? 1 : 0);
	if (raw_read) {
		mv_gpio_polarity(dev, pin, 1, 0);
		*cnt = DEBOUNCE_HI_LO_MS / DEBOUNCE_CHECK_MS;
	} else {
		mv_gpio_polarity(dev, pin, 0, 0);
		*cnt = DEBOUNCE_LO_HI_MS / DEBOUNCE_CHECK_MS;
	}

	mv_gpio_debounced_state_set(dev, pin, raw_read);

	return (0);
}