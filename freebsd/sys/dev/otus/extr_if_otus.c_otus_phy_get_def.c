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
typedef  scalar_t__ uint32_t ;
struct otus_softc {scalar_t__* phy_vals; } ;

/* Variables and functions */
 scalar_t__ AR_PHY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ar5416_phy_regs ; 
 int nitems (int /*<<< orphan*/ *) ; 

uint32_t
otus_phy_get_def(struct otus_softc *sc, uint32_t reg)
{
	int i;

	for (i = 0; i < nitems(ar5416_phy_regs); i++)
		if (AR_PHY(ar5416_phy_regs[i]) == reg)
			return sc->phy_vals[i];
	return 0;	/* Register not found. */
}