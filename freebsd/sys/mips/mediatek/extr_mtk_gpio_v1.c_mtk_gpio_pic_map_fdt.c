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
struct mtk_gpio_softc {scalar_t__ num_pins; int /*<<< orphan*/  dev; } ;
struct intr_map_data_fdt {int ncells; scalar_t__* cells; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INTR_EDGE_BOTH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
mtk_gpio_pic_map_fdt(struct mtk_gpio_softc *sc,
    struct intr_map_data_fdt *daf, u_int *irqp, uint32_t *modep)
{
	u_int irq;

	if (daf->ncells != 1) {
		device_printf(sc->dev, "Invalid #interrupt-cells\n");
		return (EINVAL);
	}

	irq = daf->cells[0];

	if (irq >= sc->num_pins) {
		device_printf(sc->dev, "Invalid interrupt number %u\n", irq);
		return (EINVAL);
	}

	*irqp = irq;
	if (modep != NULL)
		*modep = GPIO_INTR_EDGE_BOTH;

	return (0);
}