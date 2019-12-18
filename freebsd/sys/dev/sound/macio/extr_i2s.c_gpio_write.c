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
typedef  scalar_t__ u_int ;
struct aoagpio_softc {int /*<<< orphan*/  dev; } ;
typedef  enum gpio_ctrl { ____Placeholder_gpio_ctrl } gpio_ctrl ;

/* Variables and functions */
 scalar_t__ GPIO_DATA ; 
 scalar_t__ GPIO_DDR_OUTPUT ; 
 struct aoagpio_softc** gpio_ctrls ; 
 int /*<<< orphan*/  macgpio_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
gpio_write(enum gpio_ctrl ctrl, u_int x)
{
	struct aoagpio_softc 	*sc;
	u_int 			 reg;

	if ((sc = gpio_ctrls[ctrl]) == NULL)
		return;

	reg = GPIO_DDR_OUTPUT;
	if (x)
		reg |= GPIO_DATA;

	macgpio_write(sc->dev, reg);
}