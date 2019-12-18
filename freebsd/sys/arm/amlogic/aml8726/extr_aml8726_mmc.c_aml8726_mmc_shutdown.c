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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_CLEAR_IRQ ; 
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_REG ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_mmc_power_off (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  aml8726_mmc_soft_reset (struct aml8726_mmc_softc*,int) ; 
 struct aml8726_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_mmc_shutdown(device_t dev)
{
	struct aml8726_mmc_softc *sc = device_get_softc(dev);

	/*
	 * Turn off the power, reset the hardware state machine,
	 * disable the interrupts, and clear the interrupts.
	 */
	(void)aml8726_mmc_power_off(sc);
	aml8726_mmc_soft_reset(sc, false);
	CSR_WRITE_4(sc, AML_MMC_IRQ_STATUS_REG, AML_MMC_IRQ_STATUS_CLEAR_IRQ);

	return (0);
}