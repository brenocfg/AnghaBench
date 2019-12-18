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
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_spi_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_SPI_READ (struct bcm_spi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_SPI_WRITE (struct bcm_spi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_spi_modifyreg(struct bcm_spi_softc *sc, uint32_t off, uint32_t mask,
	uint32_t value)
{
	uint32_t reg;

	mtx_assert(&sc->sc_mtx, MA_OWNED);
	reg = BCM_SPI_READ(sc, off);
	reg &= ~mask;
	reg |= value;
	BCM_SPI_WRITE(sc, off, reg);
}