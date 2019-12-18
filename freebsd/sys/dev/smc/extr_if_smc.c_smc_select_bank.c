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
typedef  int uint16_t ;
struct smc_softc {int /*<<< orphan*/  smc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSR ; 
 int BSR_BANK_MASK ; 
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
smc_select_bank(struct smc_softc *sc, uint16_t bank)
{

	bus_barrier(sc->smc_reg, BSR, 2,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	bus_write_2(sc->smc_reg, BSR, bank & BSR_BANK_MASK);
	bus_barrier(sc->smc_reg, BSR, 2,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
}