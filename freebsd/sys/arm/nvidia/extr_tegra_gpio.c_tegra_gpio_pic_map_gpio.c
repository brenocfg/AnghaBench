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
typedef  int uint32_t ;
typedef  scalar_t__ u_int ;
struct tegra_gpio_softc {scalar_t__ gpio_npins; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GPIO_INTR_CONFORM 133 
#define  GPIO_INTR_EDGE_BOTH 132 
#define  GPIO_INTR_EDGE_FALLING 131 
#define  GPIO_INTR_EDGE_RISING 130 
#define  GPIO_INTR_LEVEL_HIGH 129 
#define  GPIO_INTR_LEVEL_LOW 128 
 int GPIO_INT_LVL_DELTA ; 
 int GPIO_INT_LVL_EDGE ; 
 int GPIO_INT_LVL_HIGH ; 

__attribute__((used)) static int
tegra_gpio_pic_map_gpio(struct tegra_gpio_softc *sc, u_int gpio_pin_num,
    u_int gpio_pin_flags, u_int intr_mode, u_int *irqp, uint32_t *regp)
{

	uint32_t reg;

	if (gpio_pin_num >= sc->gpio_npins)
		return (EINVAL);
	switch (intr_mode) {
	case GPIO_INTR_CONFORM:
	case GPIO_INTR_LEVEL_LOW:
		reg = 0;
		break;
	case GPIO_INTR_LEVEL_HIGH:
		reg = GPIO_INT_LVL_HIGH;
		break;
	case GPIO_INTR_EDGE_RISING:
		reg = GPIO_INT_LVL_EDGE | GPIO_INT_LVL_HIGH;
		break;
	case GPIO_INTR_EDGE_FALLING:
		reg = GPIO_INT_LVL_EDGE;
		break;
	case GPIO_INTR_EDGE_BOTH:
		reg = GPIO_INT_LVL_EDGE | GPIO_INT_LVL_DELTA;
		break;
	default:
		return (EINVAL);
	}
	*irqp = gpio_pin_num;
	if (regp != NULL)
		*regp = reg;
	return (0);
}