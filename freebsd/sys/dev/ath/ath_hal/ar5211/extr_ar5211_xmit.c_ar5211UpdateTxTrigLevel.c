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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
typedef  int HAL_INT ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 scalar_t__ AH_FALSE ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 int AR_TXCFG_FTRIG_M ; 
 int AR_TXCFG_FTRIG_S ; 
 int HAL_INT_GLOBAL ; 
 int MAX_TX_FIFO_THRESHOLD ; 
 int MIN_TX_FIFO_THRESHOLD ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int ar5211GetInterrupts (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5211SetInterrupts (struct ath_hal*,int) ; 

HAL_BOOL
ar5211UpdateTxTrigLevel(struct ath_hal *ah, HAL_BOOL bIncTrigLevel)
{
	uint32_t curTrigLevel, txcfg;
	HAL_INT ints = ar5211GetInterrupts(ah);

	/*
	 * Disable chip interrupts. This is because halUpdateTxTrigLevel
	 * is called from both ISR and non-ISR contexts.
	 */
	ar5211SetInterrupts(ah, ints &~ HAL_INT_GLOBAL);
	txcfg = OS_REG_READ(ah, AR_TXCFG);
	curTrigLevel = (txcfg & AR_TXCFG_FTRIG_M) >> AR_TXCFG_FTRIG_S;
	if (bIncTrigLevel){
		/* increase the trigger level */
		curTrigLevel = curTrigLevel +
			((MAX_TX_FIFO_THRESHOLD - curTrigLevel) / 2);
	} else {
		/* decrease the trigger level if not already at the minimum */
		if (curTrigLevel > MIN_TX_FIFO_THRESHOLD) {
			/* decrease the trigger level */
			curTrigLevel--;
		} else {
			/* no update to the trigger level */
			/* re-enable chip interrupts */
			ar5211SetInterrupts(ah, ints);
			return AH_FALSE;
		}
	}
	/* Update the trigger level */
	OS_REG_WRITE(ah, AR_TXCFG, (txcfg &~ AR_TXCFG_FTRIG_M) |
		((curTrigLevel << AR_TXCFG_FTRIG_S) & AR_TXCFG_FTRIG_M));
	/* re-enable chip interrupts */
	ar5211SetInterrupts(ah, ints);
	return AH_TRUE;
}