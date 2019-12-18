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
struct zy7_devcfg_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DEVCFG_SC_ASSERT_LOCKED (struct zy7_devcfg_softc*) ; 
 int EIO ; 
 int /*<<< orphan*/  PCATCH ; 
 int RD4 (struct zy7_devcfg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct zy7_devcfg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZY7_DEVCFG_CTRL ; 
 int ZY7_DEVCFG_CTRL_PCFG_PROG_B ; 
 int ZY7_DEVCFG_INT_ALL ; 
 int /*<<< orphan*/  ZY7_DEVCFG_INT_MASK ; 
 int ZY7_DEVCFG_INT_PCFG_INIT_PE ; 
 int /*<<< orphan*/  ZY7_DEVCFG_INT_STATUS ; 
 int /*<<< orphan*/  ZY7_DEVCFG_STATUS ; 
 int ZY7_DEVCFG_STATUS_PCFG_INIT ; 
 int /*<<< orphan*/  hz ; 
 int mtx_sleep (struct zy7_devcfg_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zy7_devcfg_reset_pl(struct zy7_devcfg_softc *sc)
{
	uint32_t devcfg_ctl;
	int tries, err;

	DEVCFG_SC_ASSERT_LOCKED(sc);

	devcfg_ctl = RD4(sc, ZY7_DEVCFG_CTRL);

	/* Clear sticky bits and set up INIT signal positive edge interrupt. */
	WR4(sc, ZY7_DEVCFG_INT_STATUS, ZY7_DEVCFG_INT_ALL);
	WR4(sc, ZY7_DEVCFG_INT_MASK, ~ZY7_DEVCFG_INT_PCFG_INIT_PE);

	/* Deassert PROG_B (active low). */
	devcfg_ctl |= ZY7_DEVCFG_CTRL_PCFG_PROG_B;
	WR4(sc, ZY7_DEVCFG_CTRL, devcfg_ctl);

	/*
	 * Wait for INIT to assert.  If it is already asserted, we may not get
	 * an edge interrupt so cancel it and continue.
	 */
	if ((RD4(sc, ZY7_DEVCFG_STATUS) &
	     ZY7_DEVCFG_STATUS_PCFG_INIT) != 0) {
		/* Already asserted.  Cancel interrupt. */
		WR4(sc, ZY7_DEVCFG_INT_MASK, ~0);
	}
	else {
		/* Wait for positive edge interrupt. */
		err = mtx_sleep(sc, &sc->sc_mtx, PCATCH, "zy7i1", hz);
		if (err != 0)
			return (err);
	}
	
	/* Reassert PROG_B (active low). */
	devcfg_ctl &= ~ZY7_DEVCFG_CTRL_PCFG_PROG_B;
	WR4(sc, ZY7_DEVCFG_CTRL, devcfg_ctl);

	/* Wait for INIT deasserted.  This happens almost instantly. */
	tries = 0;
	while ((RD4(sc, ZY7_DEVCFG_STATUS) &
		ZY7_DEVCFG_STATUS_PCFG_INIT) != 0) {
		if (++tries >= 100)
			return (EIO);
		DELAY(5);
	}

	/* Clear sticky bits and set up INIT positive edge interrupt. */
	WR4(sc, ZY7_DEVCFG_INT_STATUS, ZY7_DEVCFG_INT_ALL);
	WR4(sc, ZY7_DEVCFG_INT_MASK, ~ZY7_DEVCFG_INT_PCFG_INIT_PE);

	/* Deassert PROG_B again. */
	devcfg_ctl |= ZY7_DEVCFG_CTRL_PCFG_PROG_B;
	WR4(sc, ZY7_DEVCFG_CTRL, devcfg_ctl);

	/*
	 * Wait for INIT asserted indicating FPGA internal initialization
	 * is complete.
	 */
	err = mtx_sleep(sc, &sc->sc_mtx, PCATCH, "zy7i2", hz);
	if (err != 0)
		return (err);

	/* Clear sticky DONE bit in interrupt status. */
	WR4(sc, ZY7_DEVCFG_INT_STATUS, ZY7_DEVCFG_INT_ALL);

	return (0);
}