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
typedef  int u_int ;
struct smc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 int CR_EPH_POWER_EN ; 
 int /*<<< orphan*/  CTR ; 
 int CTR_AUTO_RELEASE ; 
 int CTR_LE_ENABLE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MMUCR ; 
 int MMUCR_CMD_MMU_RESET ; 
 int /*<<< orphan*/  MSK ; 
 int /*<<< orphan*/  RCR ; 
 int RCR_SOFT_RST ; 
 int /*<<< orphan*/  SMC_ASSERT_LOCKED (struct smc_softc*) ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  smc_mmu_wait (struct smc_softc*) ; 
 int smc_read_2 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int) ; 
 int /*<<< orphan*/  smc_write_1 (struct smc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
smc_reset(struct smc_softc *sc)
{
	u_int	ctr;

	SMC_ASSERT_LOCKED(sc);

	smc_select_bank(sc, 2);

	/*
	 * Mask all interrupts.
	 */
	smc_write_1(sc, MSK, 0);

	/*
	 * Tell the device to reset.
	 */
	smc_select_bank(sc, 0);
	smc_write_2(sc, RCR, RCR_SOFT_RST);

	/*
	 * Set up the configuration register.
	 */
	smc_select_bank(sc, 1);
	smc_write_2(sc, CR, CR_EPH_POWER_EN);
	DELAY(1);

	/*
	 * Turn off transmit and receive.
	 */
	smc_select_bank(sc, 0);
	smc_write_2(sc, TCR, 0);
	smc_write_2(sc, RCR, 0);

	/*
	 * Set up the control register.
	 */
	smc_select_bank(sc, 1);
	ctr = smc_read_2(sc, CTR);
	ctr |= CTR_LE_ENABLE | CTR_AUTO_RELEASE;
	smc_write_2(sc, CTR, ctr);

	/*
	 * Reset the MMU.
	 */
	smc_select_bank(sc, 2);
	smc_mmu_wait(sc);
	smc_write_2(sc, MMUCR, MMUCR_CMD_MMU_RESET);
}