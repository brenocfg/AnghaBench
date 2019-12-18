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
struct fpgamgr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FPGAMGR_DCLKCNT ; 
 int /*<<< orphan*/  FPGAMGR_DCLKSTAT ; 
 int READ4 (struct fpgamgr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct fpgamgr_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fpga_wait_dclk_pulses(struct fpgamgr_softc *sc, int npulses)
{
	int tout;

	/* Clear done bit, if any */
	if (READ4(sc, FPGAMGR_DCLKSTAT) != 0)
		WRITE4(sc, FPGAMGR_DCLKSTAT, 0x1);

	/* Request DCLK pulses */
	WRITE4(sc, FPGAMGR_DCLKCNT, npulses);

	/* Wait finish */
	tout = 1000;
	while (tout > 0) {
		if (READ4(sc, FPGAMGR_DCLKSTAT) == 1) {
			WRITE4(sc, FPGAMGR_DCLKSTAT, 0x1);
			break;
		}
		tout--;
		DELAY(10);
	}
	if (tout == 0) {
		return (1);
	}

	return (0);
}