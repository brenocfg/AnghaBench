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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
struct ti_gpio_softc {scalar_t__ sc_maxpin; } ;
struct intr_map_data_gpio {scalar_t__ gpio_pin_num; scalar_t__ gpio_intr_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GPIO_INTR_EDGE_BOTH ; 
 scalar_t__ GPIO_INTR_EDGE_FALLING ; 
 scalar_t__ GPIO_INTR_EDGE_RISING ; 
 scalar_t__ GPIO_INTR_LEVEL_HIGH ; 
 scalar_t__ GPIO_INTR_LEVEL_LOW ; 

__attribute__((used)) static int
ti_gpio_pic_map_gpio(struct ti_gpio_softc *sc, struct intr_map_data_gpio *dag,
    u_int *irqp, uint32_t *modep)
{
	uint32_t mode;

	if (dag->gpio_pin_num >= sc->sc_maxpin)
		return (EINVAL);

	mode = dag->gpio_intr_mode;
	if (mode != GPIO_INTR_LEVEL_LOW && mode != GPIO_INTR_LEVEL_HIGH &&
	    mode != GPIO_INTR_EDGE_RISING && mode != GPIO_INTR_EDGE_FALLING &&
	    mode != GPIO_INTR_EDGE_BOTH)
		return (EINVAL);

	*irqp = dag->gpio_pin_num;
	if (modep != NULL)
		*modep = mode;
	return (0);
}