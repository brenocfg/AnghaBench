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
struct mtk_pic_softc {scalar_t__ nirqs; } ;
struct intr_map_data_fdt {int ncells; scalar_t__* cells; } ;
struct intr_map_data {scalar_t__ type; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ INTR_MAP_DATA_FDT ; 
 struct intr_irqsrc* PIC_INTR_ISRC (struct mtk_pic_softc*,scalar_t__) ; 
 struct mtk_pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_pic_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
#ifdef FDT
	struct intr_map_data_fdt *daf;
	struct mtk_pic_softc *sc;

	if (data->type != INTR_MAP_DATA_FDT)
		return (ENOTSUP);

	sc = device_get_softc(dev);
	daf = (struct intr_map_data_fdt *)data;

	if (daf->ncells != 1 || daf->cells[0] >= sc->nirqs)
		return (EINVAL);

	*isrcp = PIC_INTR_ISRC(sc, daf->cells[0]);
	return (0);
#else
	return (ENOTSUP);
#endif
}