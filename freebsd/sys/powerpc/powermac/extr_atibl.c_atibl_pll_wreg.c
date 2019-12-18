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
struct atibl_softc {int /*<<< orphan*/  sc_memr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_DATA ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_INDEX ; 
 int /*<<< orphan*/  RADEON_CRTC_GEN_CNTL ; 
 int RADEON_PLL_WR_EN ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __inline
atibl_pll_wreg(struct atibl_softc *sc, uint32_t reg, uint32_t val)
{
	uint32_t save, tmp;

	bus_write_1(sc->sc_memr, RADEON_CLOCK_CNTL_INDEX,
	    ((reg & 0x3f) | RADEON_PLL_WR_EN));
	(void)bus_read_4(sc->sc_memr, RADEON_CLOCK_CNTL_DATA);
	(void)bus_read_4(sc->sc_memr, RADEON_CRTC_GEN_CNTL);

	bus_write_4(sc->sc_memr, RADEON_CLOCK_CNTL_DATA, val);
	DELAY(5000);

	/* Only necessary on R300, but won't hurt others. */
	save = bus_read_4(sc->sc_memr, RADEON_CLOCK_CNTL_INDEX);
	tmp = save & (~0x3f | RADEON_PLL_WR_EN);
	bus_write_4(sc->sc_memr, RADEON_CLOCK_CNTL_INDEX, tmp);
	tmp = bus_read_4(sc->sc_memr, RADEON_CLOCK_CNTL_DATA);
	bus_write_4(sc->sc_memr, RADEON_CLOCK_CNTL_INDEX, save);
}