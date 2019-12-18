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
struct sdma_softc {int dummy; } ;

/* Variables and functions */
 int READ4 (struct sdma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMAARM_DSPOVR ; 
 int /*<<< orphan*/  SDMAARM_EVTOVR ; 
 int /*<<< orphan*/  SDMAARM_HOSTOVR ; 
 int /*<<< orphan*/  WRITE4 (struct sdma_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sdma_overrides(struct sdma_softc *sc, int chn,
		int evt, int host, int dsp)
{
	int reg;

	/* Ignore sDMA requests */
	reg = READ4(sc, SDMAARM_EVTOVR);
	if (evt)
		reg |= (1 << chn);
	else
		reg &= ~(1 << chn);
	WRITE4(sc, SDMAARM_EVTOVR, reg);

	/* Ignore enable bit (HE) */
	reg = READ4(sc, SDMAARM_HOSTOVR);
	if (host)
		reg |= (1 << chn);
	else
		reg &= ~(1 << chn);
	WRITE4(sc, SDMAARM_HOSTOVR, reg);

	/* Prevent sDMA channel from starting */
	reg = READ4(sc, SDMAARM_DSPOVR);
	if (!dsp)
		reg |= (1 << chn);
	else
		reg &= ~(1 << chn);
	WRITE4(sc, SDMAARM_DSPOVR, reg);

	return (0);
}