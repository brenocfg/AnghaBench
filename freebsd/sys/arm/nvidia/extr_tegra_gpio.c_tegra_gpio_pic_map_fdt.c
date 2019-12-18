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
typedef  int u_int ;
struct tegra_gpio_softc {int gpio_npins; } ;
typedef  int pcell_t ;

/* Variables and functions */
 int EINVAL ; 
 int GPIO_INT_LVL_DELTA ; 
 int GPIO_INT_LVL_EDGE ; 
 int GPIO_INT_LVL_HIGH ; 

__attribute__((used)) static int
tegra_gpio_pic_map_fdt(struct tegra_gpio_softc *sc, u_int ncells,
    pcell_t *cells, u_int *irqp, uint32_t *regp)
{
	uint32_t reg;

	/*
	 * The first cell is the interrupt number.
	 * The second cell is used to specify flags:
	 *	bits[3:0] trigger type and level flags:
	 *		1 = low-to-high edge triggered.
	 *		2 = high-to-low edge triggered.
	 *		4 = active high level-sensitive.
	 *		8 = active low level-sensitive.
	 */
	if (ncells != 2 || cells[0] >= sc->gpio_npins)
		return (EINVAL);

	/*
	 * All interrupt types could be set for an interrupt at one moment.
	 * At least, the combination of 'low-to-high' and 'high-to-low' edge
	 * triggered interrupt types can make a sense.
	 */
	if (cells[1] == 1)
		reg = GPIO_INT_LVL_EDGE | GPIO_INT_LVL_HIGH;
	else if (cells[1] == 2)
		reg = GPIO_INT_LVL_EDGE;
	else if (cells[1] == 3)
		reg = GPIO_INT_LVL_EDGE | GPIO_INT_LVL_DELTA;
	else if (cells[1] == 4)
		reg = GPIO_INT_LVL_HIGH;
	else if (cells[1] == 8)
		reg = 0;
	else
		return (EINVAL);

	*irqp = cells[0];
	if (regp != NULL)
		*regp = reg;
	return (0);
}