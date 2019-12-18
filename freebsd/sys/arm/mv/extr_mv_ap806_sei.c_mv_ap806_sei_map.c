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
struct mv_ap806_sei_softc {int dummy; } ;
struct intr_map_data_fdt {int ncells; scalar_t__* cells; } ;
struct intr_map_data {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ INTR_MAP_DATA_FDT ; 
 scalar_t__ MV_AP806_SEI_MAX_NIRQS ; 
 struct mv_ap806_sei_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_ap806_sei_map(device_t dev, struct intr_map_data *data, u_int *irqp)
{
	struct mv_ap806_sei_softc *sc;
	struct intr_map_data_fdt *daf;
	u_int irq;

	sc = device_get_softc(dev);

	if (data->type != INTR_MAP_DATA_FDT)
		return (ENOTSUP);

	daf = (struct intr_map_data_fdt *)data;
	if (daf->ncells != 1 || daf->cells[0] >= MV_AP806_SEI_MAX_NIRQS)
		return (EINVAL);
	irq = daf->cells[0];
	if (irqp != NULL)
		*irqp = irq;

	return(0);
}