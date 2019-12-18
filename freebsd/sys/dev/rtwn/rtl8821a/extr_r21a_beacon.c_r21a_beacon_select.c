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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  R21A_DWBCN1_CTRL ; 
 int /*<<< orphan*/  R21A_DWBCN1_CTRL_SEL_BCN1 ; 
 int /*<<< orphan*/  rtwn_setbits_1_shift (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
r21a_beacon_select(struct rtwn_softc *sc, int id)
{
	switch (id) {
	case 0:
		/* Switch to port 0 beacon. */
		rtwn_setbits_1_shift(sc, R21A_DWBCN1_CTRL,
		    R21A_DWBCN1_CTRL_SEL_BCN1, 0, 2);
		break;
	case 1:
		/* Switch to port 1 beacon. */
		rtwn_setbits_1_shift(sc, R21A_DWBCN1_CTRL,
		    0, R21A_DWBCN1_CTRL_SEL_BCN1, 2);
		break;
	default:
		KASSERT(0, ("wrong port id %d\n", id));
		break;
	}
}