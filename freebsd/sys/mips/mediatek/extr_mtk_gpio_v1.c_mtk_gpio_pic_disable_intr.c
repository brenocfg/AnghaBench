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
typedef  unsigned int uint32_t ;
struct mtk_gpio_softc {int dummy; } ;
struct mtk_gpio_pin_irqsrc {unsigned int irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIOFENA ; 
 int /*<<< orphan*/  GPIO_PIORENA ; 
 int /*<<< orphan*/  MTK_GPIO_LOCK (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_UNLOCK (struct mtk_gpio_softc*) ; 
 unsigned int MTK_READ_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_WRITE_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtk_gpio_pic_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct mtk_gpio_softc *sc;
	struct mtk_gpio_pin_irqsrc *pisrc;
	uint32_t pin, mask, val;

	sc = device_get_softc(dev);

	pisrc = (struct mtk_gpio_pin_irqsrc *)isrc;
	pin = pisrc->irq;
	mask = 1u << pin;

	MTK_GPIO_LOCK(sc);

	val = MTK_READ_4(sc, GPIO_PIORENA) & ~mask;
	MTK_WRITE_4(sc, GPIO_PIORENA, val);
	val = MTK_READ_4(sc, GPIO_PIOFENA) & ~mask;
	MTK_WRITE_4(sc, GPIO_PIOFENA, val);

	MTK_GPIO_UNLOCK(sc);
}