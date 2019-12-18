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
struct mtk_spi_softc {TYPE_1__* gpio_cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CS_HIGH ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HIZSMOSI ; 
 int /*<<< orphan*/  MTK_SPICTL ; 
 int /*<<< orphan*/  SPI_CLEAR_BITS (struct mtk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_spi_wait (struct mtk_spi_softc*) ; 

__attribute__((used)) static void
mtk_spi_chip_activate(struct mtk_spi_softc *sc)
{
        mtk_spi_wait(sc);
	/*
	 * Put all CSx to low
	 */
	if (sc->gpio_cs != NULL) {
		GPIO_PIN_SET(sc->gpio_cs->dev, sc->gpio_cs->pin, 0);
		SPI_CLEAR_BITS(sc, MTK_SPICTL, HIZSMOSI);
	} else {
		SPI_CLEAR_BITS(sc, MTK_SPICTL, CS_HIGH | HIZSMOSI);
	}
}