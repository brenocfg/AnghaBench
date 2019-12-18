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
typedef  int /*<<< orphan*/  u_int ;
struct mtk_gpio_softc {int dummy; } ;
struct intr_map_data_gpio {int dummy; } ;
struct intr_map_data_fdt {int dummy; } ;
struct intr_map_data {int type; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
#define  INTR_MAP_DATA_FDT 129 
#define  INTR_MAP_DATA_GPIO 128 
 struct intr_irqsrc* PIC_INTR_ISRC (struct mtk_gpio_softc*,int /*<<< orphan*/ ) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mtk_gpio_pic_map_fdt (struct mtk_gpio_softc*,struct intr_map_data_fdt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mtk_gpio_pic_map_gpio (struct mtk_gpio_softc*,struct intr_map_data_gpio*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mtk_gpio_pic_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
	int error;
	u_int irq;
	struct mtk_gpio_softc *sc;

	sc = device_get_softc(dev);
	switch (data->type) {
	case INTR_MAP_DATA_FDT:
		error = (mtk_gpio_pic_map_fdt(sc, 
		    (struct intr_map_data_fdt *)data, &irq, NULL));
		break;
	case INTR_MAP_DATA_GPIO:
		error = (mtk_gpio_pic_map_gpio(sc, 
		    (struct intr_map_data_gpio *)data, &irq, NULL));
		break;
	default:
		error = EINVAL;
		break;
	}

	if (error != 0) {
		device_printf(dev, "Invalid map type\n");
		return (error);
	}

	*isrcp = PIC_INTR_ISRC(sc, irq);
	return (0);
}