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
typedef  int uint8_t ;
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int pmu_read_reg (struct pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_write_reg (struct pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vACR ; 
 int vSR_OUT ; 

__attribute__((used)) static void
pmu_out(struct pmu_softc *sc)
{
	uint8_t reg;

	reg = pmu_read_reg(sc, vACR);
	reg |= vSR_OUT;
	reg |= 0x0c;
	pmu_write_reg(sc, vACR, reg);
}