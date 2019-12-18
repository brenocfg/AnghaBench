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
struct mtk_spi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_SPIPOLAR ; 
 int /*<<< orphan*/  SPI_CLEAR_BITS (struct mtk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_spi_wait (struct mtk_spi_softc*) ; 

__attribute__((used)) static void
mtk_spi_chip_deactivate(struct mtk_spi_softc *sc)
{
        mtk_spi_wait(sc);
	/*
	 * Put all CSx to high
	 */
	SPI_CLEAR_BITS(sc, MTK_SPIPOLAR, 1);
}