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
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int pmu_read_reg (struct pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vBufB ; 
 int vPB3 ; 

__attribute__((used)) static int
pmu_intr_state(struct pmu_softc *sc)
{
	return ((pmu_read_reg(sc, vBufB) & vPB3) == 0);
}