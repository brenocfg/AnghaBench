#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_ispcie; } ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PCIE_SERDES ; 
 int /*<<< orphan*/  AR_PCIE_SERDES2 ; 
 scalar_t__ AR_SREV_OWL (struct ath_hal*) ; 
 scalar_t__ AR_SREV_OWL_20_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE_BUFFER_DISABLE (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE_BUFFER_ENABLE (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE_BUFFER_FLUSH (struct ath_hal*) ; 

__attribute__((used)) static void
ar5416DisablePCIE(struct ath_hal *ah)
{

	/* PCIe? Don't */
	if (AH_PRIVATE(ah)->ah_ispcie)
		return;

	/* .. Only applicable for AR5416v2 or later */
	if (! (AR_SREV_OWL(ah) && AR_SREV_OWL_20_OR_LATER(ah)))
		return;

	OS_REG_WRITE_BUFFER_ENABLE(ah);

	/*
	 * Disable the PCIe PHY.
	 */
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x9248fc00);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x24924924);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x28000029);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x57160824);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x25980579);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x00000000);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x1aaabe40);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0xbe105554);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x000e1007);

	/* Load the new settings */
	OS_REG_WRITE(ah, AR_PCIE_SERDES2, 0x00000000);

	OS_REG_WRITE_BUFFER_FLUSH(ah);
	OS_REG_WRITE_BUFFER_DISABLE(ah);
}