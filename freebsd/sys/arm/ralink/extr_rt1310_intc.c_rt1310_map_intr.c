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
struct rt1310_intc_softc {TYPE_1__* ri_isrcs; } ;
struct intr_map_data_fdt {int ncells; size_t* cells; } ;
struct intr_map_data {scalar_t__ type; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct intr_irqsrc ri_isrc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 size_t INTC_NIRQS ; 
 scalar_t__ INTR_MAP_DATA_FDT ; 
 struct rt1310_intc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rt1310_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
	struct intr_map_data_fdt *daf;
	struct rt1310_intc_softc *sc;

	if (data->type != INTR_MAP_DATA_FDT)
		return (ENOTSUP);

	daf = (struct intr_map_data_fdt *)data;

	if (daf->ncells != 1 || daf->cells[0] >= INTC_NIRQS)
		return (EINVAL);

	sc = device_get_softc(dev);
	*isrcp = &sc->ri_isrcs[daf->cells[0]].ri_isrc;
	return (0);
}