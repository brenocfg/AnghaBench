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
struct pl310_softc {int sc_io_coherent; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  PL310_POWER_CTRL ; 
 int /*<<< orphan*/  PL310_PREFETCH_CTRL ; 
 int POWER_CTRL_ENABLE_GATING ; 
 int PREFETCH_CTRL_DATA_PREFETCH ; 
 int PREFETCH_CTRL_DL ; 
 int PREFETCH_CTRL_DL_ON_WRAP ; 
 int PREFETCH_CTRL_INCR_DL ; 
 int pl310_read4 (struct pl310_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl310_write4 (struct pl310_softc*,int /*<<< orphan*/ ,int) ; 

void
mv_a38x_platform_pl310_init(platform_t plat, struct pl310_softc *sc)
{
	uint32_t reg;

	/*
	 * Enable power saving modes:
	 *  - Dynamic Gating stops the clock when the controller is idle.
	 */
	reg = pl310_read4(sc, PL310_POWER_CTRL);
	reg |= POWER_CTRL_ENABLE_GATING;
	pl310_write4(sc, PL310_POWER_CTRL, reg);

	pl310_write4(sc, PL310_PREFETCH_CTRL, PREFETCH_CTRL_DL |
	    PREFETCH_CTRL_DATA_PREFETCH | PREFETCH_CTRL_INCR_DL |
	    PREFETCH_CTRL_DL_ON_WRAP);

	/* Disable L2 cache sync for IO coherent operation */
	sc->sc_io_coherent = true;
}