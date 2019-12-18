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
struct mtk_gpio_softc {int dummy; } ;
struct mtk_gpio_pin_irqsrc {unsigned int irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIOINT ; 
 int /*<<< orphan*/  MTK_GPIO_LOCK (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_GPIO_UNLOCK (struct mtk_gpio_softc*) ; 
 int /*<<< orphan*/  MTK_WRITE_4 (struct mtk_gpio_softc*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mtk_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtk_gpio_pic_post_filter(device_t dev, struct intr_irqsrc *isrc)
{
	struct mtk_gpio_softc *sc;
	struct mtk_gpio_pin_irqsrc *pisrc;

	pisrc = (struct mtk_gpio_pin_irqsrc *)isrc;
	sc = device_get_softc(dev);
	MTK_GPIO_LOCK(sc);
	MTK_WRITE_4(sc, GPIO_PIOINT, 1u << pisrc->irq);
	MTK_GPIO_UNLOCK(sc);
}