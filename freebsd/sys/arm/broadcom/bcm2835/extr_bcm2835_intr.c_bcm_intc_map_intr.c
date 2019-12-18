#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct intr_map_data_fdt {int ncells; size_t* cells; } ;
struct intr_map_data {scalar_t__ type; } ;
struct intr_irqsrc {int dummy; } ;
struct bcm_intc_softc {TYPE_1__* intc_isrcs; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct intr_irqsrc bii_isrc; } ;

/* Variables and functions */
 size_t BANK1_END ; 
 size_t BANK1_START ; 
 size_t BANK2_END ; 
 int /*<<< orphan*/  BANK2_START ; 
 size_t BCM_INTC_NIRQS ; 
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ INTR_MAP_DATA_FDT ; 
 struct bcm_intc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static int
bcm_intc_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
	u_int irq;
	struct intr_map_data_fdt *daf;
	struct bcm_intc_softc *sc;
	bool valid;

	if (data->type != INTR_MAP_DATA_FDT)
		return (ENOTSUP);

	daf = (struct intr_map_data_fdt *)data;
	if (daf->ncells == 1)
		irq = daf->cells[0];
	else if (daf->ncells == 2) {
		valid = true;
		switch (daf->cells[0]) {
		case 0:
			irq = daf->cells[1];
			if (irq >= BANK1_START)
				valid = false;
			break;
		case 1:
			irq = daf->cells[1] + BANK1_START;
			if (irq > BANK1_END)
				valid = false;
			break;
		case 2:
			irq = daf->cells[1] + BANK2_START;
			if (irq > BANK2_END)
				valid = false;
			break;
		default:
			valid = false;
			break;
		}

		if (!valid) {
			device_printf(dev,
			    "invalid IRQ config: bank=%d, irq=%d\n",
			    daf->cells[0], daf->cells[1]);
			return (EINVAL);
		}
	}
	else
		return (EINVAL);

	if (irq >= BCM_INTC_NIRQS)
		return (EINVAL);

	sc = device_get_softc(dev);
	*isrcp = &sc->intc_isrcs[irq].bii_isrc;
	return (0);
}