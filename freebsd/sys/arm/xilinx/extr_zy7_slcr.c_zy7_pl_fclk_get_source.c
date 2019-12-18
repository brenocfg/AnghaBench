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
struct zy7_slcr_softc {int dummy; } ;

/* Variables and functions */
 int RD4 (struct zy7_slcr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSLCR_LOCK (struct zy7_slcr_softc*) ; 
 int /*<<< orphan*/  ZSLCR_UNLOCK (struct zy7_slcr_softc*) ; 
 int ZY7_PL_FCLK_SRC_IO ; 
 int /*<<< orphan*/  ZY7_SLCR_FPGA_CLK_CTRL (int) ; 
 int ZY7_SLCR_FPGA_CLK_CTRL_SRCSEL_MASK ; 
 int ZY7_SLCR_FPGA_CLK_CTRL_SRCSEL_SHIFT ; 
 struct zy7_slcr_softc* zy7_slcr_softc_p ; 

int 
zy7_pl_fclk_get_source(int unit)
{
	struct zy7_slcr_softc *sc = zy7_slcr_softc_p;
	uint32_t reg;
	int source;

	if (!sc)
		return (-1);

	ZSLCR_LOCK(sc);

	/* Modify GEM reference clock. */
	reg = RD4(sc, ZY7_SLCR_FPGA_CLK_CTRL(unit));
	source = (reg & ZY7_SLCR_FPGA_CLK_CTRL_SRCSEL_MASK) >> 
	    ZY7_SLCR_FPGA_CLK_CTRL_SRCSEL_SHIFT;

	/* ZY7_PL_FCLK_SRC_IO is actually b0x */
	if ((source & 2) == 0)
		source = ZY7_PL_FCLK_SRC_IO;

	ZSLCR_UNLOCK(sc);

	return (source);
}