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
struct nvbl_softc {int /*<<< orphan*/  sc_memr; } ;

/* Variables and functions */
 int NVIDIA_BRIGHT_MIN ; 
 int NVIDIA_BRIGHT_SCALE ; 
 int NVIDIA_PMC_BL_EN ; 
 int NVIDIA_PMC_BL_SHIFT ; 
 int /*<<< orphan*/  NVIDIA_PMC_OFF ; 
 int bus_read_stream_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_stream_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nvbl_setlevel(struct nvbl_softc *sc, int newlevel)
{
	uint32_t pmc_reg;

	if (newlevel > 100)
		newlevel = 100;

	if (newlevel < 0)
		newlevel = 0;

	if (newlevel > 0)
		newlevel = (newlevel * NVIDIA_BRIGHT_SCALE) + NVIDIA_BRIGHT_MIN;

	pmc_reg = bus_read_stream_4(sc->sc_memr, NVIDIA_PMC_OFF) & 0xffff;
	pmc_reg |= NVIDIA_PMC_BL_EN | (newlevel << NVIDIA_PMC_BL_SHIFT);
	bus_write_stream_4(sc->sc_memr, NVIDIA_PMC_OFF, pmc_reg);

	return (0);
}