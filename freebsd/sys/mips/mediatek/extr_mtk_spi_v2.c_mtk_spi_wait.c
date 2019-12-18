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
 int /*<<< orphan*/  MTK_SPITRANS ; 
 int SPIBUSY ; 
 int SPI_READ (struct mtk_spi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_spi_wait(struct mtk_spi_softc *sc)
{
	int i = 1000;

	while (i--) {
		if (!(SPI_READ(sc, MTK_SPITRANS) & SPIBUSY))
			break;
	}
	if (i == 0) {
		return (1);
	}

	return (0);
}