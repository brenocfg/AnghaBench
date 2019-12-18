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
 int /*<<< orphan*/  FPGAMGR_STAT ; 
 int READ4 (struct fpgamgr_softc*,int /*<<< orphan*/ ) ; 
 int STAT_MODE_MASK ; 
 int STAT_MODE_SHIFT ; 

__attribute__((used)) static int
fpgamgr_state_get(struct fpgamgr_softc *sc)
{
	int reg;

	reg = READ4(sc, FPGAMGR_STAT);
	reg >>= STAT_MODE_SHIFT;
	reg &= STAT_MODE_MASK;

	return reg;
}