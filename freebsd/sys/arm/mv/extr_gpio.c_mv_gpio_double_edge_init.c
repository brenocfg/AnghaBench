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
struct mv_gpio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MV_GPIO_ASSERT_LOCKED () ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_polarity (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mv_gpio_value_get (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
mv_gpio_double_edge_init(device_t dev, int pin)
{
	uint8_t raw_read;
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	MV_GPIO_ASSERT_LOCKED();

	raw_read = (mv_gpio_value_get(dev, pin, 1) ? 1 : 0);

	if (raw_read)
		mv_gpio_polarity(dev, pin, 1, 0);
	else
		mv_gpio_polarity(dev, pin, 0, 0);
}