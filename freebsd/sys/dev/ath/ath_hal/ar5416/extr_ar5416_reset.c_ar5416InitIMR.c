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
struct ath_hal_5212 {int ah_maskReg; } ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_OPMODE ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_IMR ; 
 int AR_IMR_BCNMISC ; 
 int AR_IMR_MIB ; 
 int AR_IMR_RXERR ; 
 int AR_IMR_RXINTM ; 
 int AR_IMR_RXMINTR ; 
 int AR_IMR_RXOK ; 
 int AR_IMR_RXORN ; 
 int /*<<< orphan*/  AR_IMR_S2 ; 
 int AR_IMR_S2_CST ; 
 int AR_IMR_S2_GTT ; 
 int AR_IMR_TXERR ; 
 int AR_IMR_TXOK ; 
 int AR_IMR_TXURN ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE ; 
 int AR_INTR_SYNC_DEFAULT ; 
 int /*<<< orphan*/  AR_INTR_SYNC_ENABLE ; 
 int /*<<< orphan*/  AR_INTR_SYNC_MASK ; 
 int /*<<< orphan*/  AR_SREV_HOWL (struct ath_hal*) ; 
 scalar_t__ HAL_M_HOSTAP ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5416InitIMR(struct ath_hal *ah, HAL_OPMODE opmode)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	/*
	 * Setup interrupt handling.  Note that ar5212ResetTxQueue
	 * manipulates the secondary IMR's as queues are enabled
	 * and disabled.  This is done with RMW ops to insure the
	 * settings we make here are preserved.
	 */
        ahp->ah_maskReg = AR_IMR_TXERR | AR_IMR_TXURN
			| AR_IMR_RXERR | AR_IMR_RXORN
                        | AR_IMR_BCNMISC;

#ifdef	AH_AR5416_INTERRUPT_MITIGATION
	ahp->ah_maskReg |= AR_IMR_RXINTM | AR_IMR_RXMINTR;
#else
	ahp->ah_maskReg |= AR_IMR_RXOK;
#endif	
	ahp->ah_maskReg |= AR_IMR_TXOK;

	if (opmode == HAL_M_HOSTAP)
		ahp->ah_maskReg |= AR_IMR_MIB;
	OS_REG_WRITE(ah, AR_IMR, ahp->ah_maskReg);

#ifdef  ADRIAN_NOTYET
	/* This is straight from ath9k */
	if (! AR_SREV_HOWL(ah)) {
		OS_REG_WRITE(ah, AR_INTR_SYNC_CAUSE, 0xFFFFFFFF);
		OS_REG_WRITE(ah, AR_INTR_SYNC_ENABLE, AR_INTR_SYNC_DEFAULT);
		OS_REG_WRITE(ah, AR_INTR_SYNC_MASK, 0);
	}
#endif

	/* Enable bus errors that are OR'd to set the HIUERR bit */
#if 0
	OS_REG_WRITE(ah, AR_IMR_S2, 
	    	OS_REG_READ(ah, AR_IMR_S2) | AR_IMR_S2_GTT | AR_IMR_S2_CST);
#endif
}