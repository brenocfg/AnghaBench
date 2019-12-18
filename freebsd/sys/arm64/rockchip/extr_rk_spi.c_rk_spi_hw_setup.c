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
typedef  int uint32_t ;
struct rk_spi_softc {int max_freq; int /*<<< orphan*/  clk_spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_ROUND_DOWN ; 
 int CTRLR0_BHT_8BIT ; 
 int CTRLR0_DFS_8BIT ; 
 int CTRLR0_EM_BIG ; 
 int CTRLR0_FRF_MOTO ; 
 int CTRLR0_OPM_MASTER ; 
 int CTRLR0_SCPH ; 
 int CTRLR0_SCPOL ; 
 int CTRLR0_SSD_ONE ; 
 int CTRLR0_XFM_TR ; 
 int /*<<< orphan*/  RK_SPI_BAUDR ; 
 int /*<<< orphan*/  RK_SPI_CTRLR0 ; 
 int /*<<< orphan*/  RK_SPI_WRITE_4 (struct rk_spi_softc*,int /*<<< orphan*/ ,int) ; 
 int SPIBUS_MODE_CPHA ; 
 int SPIBUS_MODE_CPOL ; 
 int /*<<< orphan*/  clk_get_freq (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rk_spi_hw_setup(struct rk_spi_softc *sc, uint32_t mode, uint32_t freq)
{
	uint32_t cr0;
	uint32_t div;

	cr0 =  CTRLR0_OPM_MASTER | CTRLR0_XFM_TR | CTRLR0_FRF_MOTO |
	    CTRLR0_BHT_8BIT | CTRLR0_EM_BIG | CTRLR0_SSD_ONE |
	    CTRLR0_DFS_8BIT;

	if (mode & SPIBUS_MODE_CPHA)
		cr0 |= CTRLR0_SCPH;
	if (mode & SPIBUS_MODE_CPOL)
		cr0 |= CTRLR0_SCPOL;

	/* minimum divider is 2 */
	if (sc->max_freq < freq*2) {
		clk_set_freq(sc->clk_spi, 2 * freq, CLK_SET_ROUND_DOWN);
		clk_get_freq(sc->clk_spi, &sc->max_freq);
	}

	div = ((sc->max_freq + freq - 1) / freq);
	div = (div + 1) & 0xfffe;
	RK_SPI_WRITE_4(sc, RK_SPI_BAUDR, div);

	RK_SPI_WRITE_4(sc, RK_SPI_CTRLR0, cr0);
}