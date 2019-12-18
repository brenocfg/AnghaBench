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
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_CR ; 
 int /*<<< orphan*/  AR_CR_RXD ; 
 int AR_CR_RXE ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,...) ; 

HAL_BOOL
ar5210StopDmaReceive(struct ath_hal *ah)
{
	int i;

	OS_REG_WRITE(ah, AR_CR, AR_CR_RXD);	/* Set receive disable bit */
	for (i = 0; i < 1000; i++) {
		if ((OS_REG_READ(ah, AR_CR) & AR_CR_RXE) == 0)
			return AH_TRUE;
		OS_DELAY(10);
	}
#ifdef AH_DEBUG
	ath_hal_printf(ah, "ar5210: dma receive failed to stop in 10ms\n");
	ath_hal_printf(ah, "AR_CR=0x%x\n", OS_REG_READ(ah, AR_CR));
	ath_hal_printf(ah, "AR_DIAG_SW=0x%x\n", OS_REG_READ(ah, AR_DIAG_SW));
#endif
	return AH_FALSE;
}