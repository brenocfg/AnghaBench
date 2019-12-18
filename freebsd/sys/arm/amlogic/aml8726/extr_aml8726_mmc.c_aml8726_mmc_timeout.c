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
struct aml8726_mmc_softc {int dummy; } ;

/* Variables and functions */
 int AML_MMC_IRQ_STATUS_CMD_BUSY ; 
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_REG ; 
 int CSR_READ_4 (struct aml8726_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_ERR_TIMEOUT ; 
 int /*<<< orphan*/  aml8726_mmc_finish_command (struct aml8726_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_mmc_soft_reset (struct aml8726_mmc_softc*,int) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 

__attribute__((used)) static void
aml8726_mmc_timeout(void *arg)
{
	struct aml8726_mmc_softc *sc = (struct aml8726_mmc_softc *)arg;

	/*
	 * The command failed to complete in time so forcefully
	 * terminate it.
	 */
	aml8726_mmc_soft_reset(sc, false);

	/*
	 * Ensure the command has terminated before continuing on
	 * to things such as bus_dmamap_sync / bus_dmamap_unload.
	 */
	while ((CSR_READ_4(sc, AML_MMC_IRQ_STATUS_REG) &
	    AML_MMC_IRQ_STATUS_CMD_BUSY) != 0)
		cpu_spinwait();

	aml8726_mmc_finish_command(sc, MMC_ERR_TIMEOUT);
}