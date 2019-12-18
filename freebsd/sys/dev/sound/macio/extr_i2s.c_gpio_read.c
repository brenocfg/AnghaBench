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
typedef  int u_int ;
struct aoagpio_softc {int /*<<< orphan*/  dev; } ;
typedef  enum gpio_ctrl { ____Placeholder_gpio_ctrl } gpio_ctrl ;

/* Variables and functions */
 int GPIO_DATA ; 
 struct aoagpio_softc** gpio_ctrls ; 
 int macgpio_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
gpio_read(enum gpio_ctrl ctrl)
{
	struct aoagpio_softc *sc;

	if ((sc = gpio_ctrls[ctrl]) == NULL)
		return (0);

	return (macgpio_read(sc->dev) & GPIO_DATA);
}