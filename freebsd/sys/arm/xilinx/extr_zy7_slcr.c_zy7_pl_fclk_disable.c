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
struct zy7_slcr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WR4 (struct zy7_slcr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSLCR_LOCK (struct zy7_slcr_softc*) ; 
 int /*<<< orphan*/  ZSLCR_UNLOCK (struct zy7_slcr_softc*) ; 
 int /*<<< orphan*/  ZY7_SLCR_FPGA_THR_CNT (int) ; 
 int /*<<< orphan*/  ZY7_SLCR_FPGA_THR_CTRL (int) ; 
 int /*<<< orphan*/  zy7_slcr_lock (struct zy7_slcr_softc*) ; 
 struct zy7_slcr_softc* zy7_slcr_softc_p ; 
 int /*<<< orphan*/  zy7_slcr_unlock (struct zy7_slcr_softc*) ; 

int 
zy7_pl_fclk_disable(int unit)
{
	struct zy7_slcr_softc *sc = zy7_slcr_softc_p;

	if (!sc)
		return (-1);

	ZSLCR_LOCK(sc);

	/* Unlock SLCR registers. */
	zy7_slcr_unlock(sc);

	WR4(sc, ZY7_SLCR_FPGA_THR_CTRL(unit), 0);
	WR4(sc, ZY7_SLCR_FPGA_THR_CNT(unit), 1);

	/* Lock SLCR registers. */
	zy7_slcr_lock(sc);

	ZSLCR_UNLOCK(sc);

	return (0);
}