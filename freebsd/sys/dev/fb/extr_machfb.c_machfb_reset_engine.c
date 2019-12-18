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
struct machfb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CNTL ; 
 int BUS_FIFO_ERR_ACK ; 
 int BUS_HOST_ERR_ACK ; 
 int /*<<< orphan*/  GEN_TEST_CNTL ; 
 int GUI_ENGINE_ENABLE ; 
 int regr (struct machfb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (struct machfb_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
machfb_reset_engine(struct machfb_softc *sc)
{

	/* Reset engine.*/
	regw(sc, GEN_TEST_CNTL, regr(sc, GEN_TEST_CNTL) & ~GUI_ENGINE_ENABLE);

	/* Enable engine. */
	regw(sc, GEN_TEST_CNTL, regr(sc, GEN_TEST_CNTL) | GUI_ENGINE_ENABLE);

	/*
	 * Ensure engine is not locked up by clearing any FIFO or
	 * host errors.
	 */
	regw(sc, BUS_CNTL, regr(sc, BUS_CNTL) | BUS_HOST_ERR_ACK |
	    BUS_FIFO_ERR_ACK);
}