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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PCIE_SERDES ; 
 int /*<<< orphan*/  AR_PCIE_SERDES2 ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5212ConfigPCIE(struct ath_hal *ah, HAL_BOOL restore, HAL_BOOL power_off)
{
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x9248fc00);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x24924924);

	/* RX shut off when elecidle is asserted */
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x28000039);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x53160824);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0xe5980579);
                                                                                           
	/* Shut off PLL and CLKREQ active in L1 */
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x001defff);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x1aaabe40);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0xbe105554);
	OS_REG_WRITE(ah, AR_PCIE_SERDES, 0x000e3007);
                                                                                           
	/* Load the new settings */
	OS_REG_WRITE(ah, AR_PCIE_SERDES2, 0x00000000);
}