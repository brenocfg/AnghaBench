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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct intr_map_data_fdt {int ncells; scalar_t__* cells; } ;
struct bcm_gpio_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCM_GPIO_PINS ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INTR_EDGE_BOTH ; 
 int /*<<< orphan*/  GPIO_INTR_EDGE_FALLING ; 
 int /*<<< orphan*/  GPIO_INTR_EDGE_RISING ; 
 int /*<<< orphan*/  GPIO_INTR_LEVEL_HIGH ; 
 int /*<<< orphan*/  GPIO_INTR_LEVEL_LOW ; 
 scalar_t__ bcm_gpio_pin_is_ro (struct bcm_gpio_softc*,scalar_t__) ; 

__attribute__((used)) static int
bcm_gpio_pic_map_fdt(struct bcm_gpio_softc *sc, struct intr_map_data_fdt *daf,
    u_int *irqp, uint32_t *modep)
{
	u_int irq;
	uint32_t mode;

	/*
	 * The first cell is the interrupt number.
	 * The second cell is used to specify flags:
	 *	bits[3:0] trigger type and level flags:
	 *		1 = low-to-high edge triggered.
	 *		2 = high-to-low edge triggered.
	 *		4 = active high level-sensitive.
	 *		8 = active low level-sensitive.
	 */
	if (daf->ncells != 2)
		return (EINVAL);

	irq = daf->cells[0];
	if (irq >= BCM_GPIO_PINS || bcm_gpio_pin_is_ro(sc, irq))
		return (EINVAL);

	/* Only reasonable modes are supported. */
	if (daf->cells[1] == 1)
		mode = GPIO_INTR_EDGE_RISING;
	else if (daf->cells[1] == 2)
		mode = GPIO_INTR_EDGE_FALLING;
	else if (daf->cells[1] == 3)
		mode = GPIO_INTR_EDGE_BOTH;
	else if (daf->cells[1] == 4)
		mode = GPIO_INTR_LEVEL_HIGH;
	else if (daf->cells[1] == 8)
		mode = GPIO_INTR_LEVEL_LOW;
	else
		return (EINVAL);

	*irqp = irq;
	if (modep != NULL)
		*modep = mode;
	return (0);
}