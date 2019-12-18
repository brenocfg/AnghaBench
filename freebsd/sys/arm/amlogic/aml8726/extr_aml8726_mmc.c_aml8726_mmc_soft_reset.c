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
typedef  int /*<<< orphan*/  uint32_t ;
struct aml8726_mmc_softc {int dummy; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_IRQ_CONFIG_CMD_DONE_EN ; 
 int /*<<< orphan*/  AML_MMC_IRQ_CONFIG_REG ; 
 int /*<<< orphan*/  AML_MMC_IRQ_CONFIG_SOFT_RESET ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aml8726_mmc_soft_reset(struct aml8726_mmc_softc *sc, boolean_t enable_irq)
{
	uint32_t icr;

	icr = AML_MMC_IRQ_CONFIG_SOFT_RESET;

	if (enable_irq == true)
		icr |= AML_MMC_IRQ_CONFIG_CMD_DONE_EN;

	CSR_WRITE_4(sc, AML_MMC_IRQ_CONFIG_REG, icr);
	CSR_BARRIER(sc, AML_MMC_IRQ_CONFIG_REG);
}