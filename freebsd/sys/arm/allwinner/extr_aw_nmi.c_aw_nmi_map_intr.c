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
typedef  int /*<<< orphan*/  u_int ;
struct intr_map_data_fdt {int /*<<< orphan*/  cells; int /*<<< orphan*/  ncells; } ;
struct intr_map_data {scalar_t__ type; } ;
struct intr_irqsrc {int dummy; } ;
struct TYPE_2__ {struct intr_irqsrc isrc; } ;
struct aw_nmi_softc {TYPE_1__ intr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ INTR_MAP_DATA_FDT ; 
 int aw_nmi_map_fdt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct aw_nmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_nmi_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
	struct intr_map_data_fdt *daf;
	struct aw_nmi_softc *sc;
	int error;
	u_int irq;

	if (data->type != INTR_MAP_DATA_FDT)
		return (ENOTSUP);

	sc = device_get_softc(dev);
	daf = (struct intr_map_data_fdt *)data;

	error = aw_nmi_map_fdt(dev, daf->ncells, daf->cells, &irq, NULL, NULL);
	if (error == 0)
		*isrcp = &sc->intr.isrc;

	return (error);
}