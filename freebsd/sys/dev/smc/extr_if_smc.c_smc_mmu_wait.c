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
struct smc_softc {int /*<<< orphan*/  smc_reg; int /*<<< orphan*/  smc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSR ; 
 int BSR_BANK_MASK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MMUCR ; 
 int MMUCR_BUSY ; 
 int bus_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
smc_mmu_wait(struct smc_softc *sc)
{

	KASSERT((bus_read_2(sc->smc_reg, BSR) &
	    BSR_BANK_MASK) == 2, ("%s: smc_mmu_wait called when not in bank 2",
	    device_get_nameunit(sc->smc_dev)));
	while (bus_read_2(sc->smc_reg, MMUCR) & MMUCR_BUSY)
		;
}