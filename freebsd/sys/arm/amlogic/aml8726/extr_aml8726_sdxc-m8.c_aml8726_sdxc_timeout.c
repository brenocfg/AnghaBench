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
struct aml8726_sdxc_softc {int dummy; } ;

/* Variables and functions */
 int AML_SDXC_STATUS_BUSY ; 
 int /*<<< orphan*/  AML_SDXC_STATUS_REG ; 
 int CSR_READ_4 (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_ERR_TIMEOUT ; 
 int /*<<< orphan*/  aml8726_sdxc_finish_command (struct aml8726_sdxc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_sdxc_soft_reset (struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 

__attribute__((used)) static void
aml8726_sdxc_timeout(void *arg)
{
	struct aml8726_sdxc_softc *sc = (struct aml8726_sdxc_softc *)arg;

	/*
	 * The command failed to complete in time so forcefully
	 * terminate it.
	 */
	aml8726_sdxc_soft_reset(sc);

	/*
	 * Ensure the command has terminated before continuing on
	 * to things such as bus_dmamap_sync / bus_dmamap_unload.
	 */
	while ((CSR_READ_4(sc, AML_SDXC_STATUS_REG) &
	    AML_SDXC_STATUS_BUSY) != 0)
		cpu_spinwait();

	aml8726_sdxc_finish_command(sc, MMC_ERR_TIMEOUT);
}