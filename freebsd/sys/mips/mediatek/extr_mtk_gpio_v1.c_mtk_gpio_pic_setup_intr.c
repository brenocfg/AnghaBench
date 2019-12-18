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
typedef  unsigned int u_int ;
struct resource {int dummy; } ;
struct mtk_gpio_softc {int dummy; } ;
struct intr_map_data_gpio {int dummy; } ;
struct intr_map_data_fdt {int dummy; } ;
struct intr_map_data {int type; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ GPIO_INTR_EDGE_BOTH ; 
 scalar_t__ GPIO_INTR_EDGE_FALLING ; 
 scalar_t__ GPIO_INTR_EDGE_RISING ; 
 int /*<<< orphan*/  GPIO_PIOFENA ; 
 int /*<<< orphan*/  GPIO_PIORENA ; 
#define  INTR_MAP_DATA_FDT 129 
#define  INTR_MAP_DATA_GPIO 128 
 int /*<<< orphan*/  MTK_GPIO_LOCK (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_UNLOCK (struct mtk_gpio_softc*) ; 
 unsigned int MTK_READ_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_WRITE_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtk_gpio_pic_map_fdt (struct mtk_gpio_softc*,struct intr_map_data_fdt*,unsigned int*,scalar_t__*) ; 
 int mtk_gpio_pic_map_gpio (struct mtk_gpio_softc*,struct intr_map_data_gpio*,unsigned int*,scalar_t__*) ; 

__attribute__((used)) static int
mtk_gpio_pic_setup_intr(device_t dev, struct intr_irqsrc *isrc,
    struct resource *res, struct intr_map_data *data)
{
	struct mtk_gpio_softc *sc;
	uint32_t val;
	int error;
	uint32_t mode;
	u_int irq;

	if (data == NULL)
		return (ENOTSUP);

	sc = device_get_softc(dev);

	switch (data->type) {
	case INTR_MAP_DATA_FDT:
		error = mtk_gpio_pic_map_fdt(sc, 
		    (struct intr_map_data_fdt *)data, &irq, &mode);
		break;
	case INTR_MAP_DATA_GPIO:
		error = mtk_gpio_pic_map_gpio(sc, 
		    (struct intr_map_data_gpio *)data, &irq, &mode);
		break;
	default:
		error = ENOTSUP;
		break;
	}

	if (error != 0)
		return (error);
	
	MTK_GPIO_LOCK(sc);
	if (mode == GPIO_INTR_EDGE_BOTH || mode == GPIO_INTR_EDGE_RISING) {
		val = MTK_READ_4(sc, GPIO_PIORENA) | (1u << irq);
		MTK_WRITE_4(sc, GPIO_PIORENA, val);
	}
	if (mode == GPIO_INTR_EDGE_BOTH || mode == GPIO_INTR_EDGE_FALLING) {
		val = MTK_READ_4(sc, GPIO_PIOFENA) | (1u << irq);
		MTK_WRITE_4(sc, GPIO_PIOFENA, val);
	}
	MTK_GPIO_UNLOCK(sc);
	return (0);
}