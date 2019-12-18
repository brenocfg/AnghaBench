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
struct ath_hal_private {int /*<<< orphan*/  ah_opmode; int /*<<< orphan*/  ah_curchan; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_MARK_RX_CTL ; 
 int /*<<< orphan*/  AH_MARK_RX_CTL_PCU_START ; 
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  OS_MARK (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5212AniReset (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5212EnableMibCounters (struct ath_hal*) ; 

void
ar5212StartPcuReceive(struct ath_hal *ah, HAL_BOOL is_scanning)
{
	struct ath_hal_private *ahp = AH_PRIVATE(ah);

	OS_MARK(ah, AH_MARK_RX_CTL, AH_MARK_RX_CTL_PCU_START);
	OS_REG_WRITE(ah, AR_DIAG_SW,
		OS_REG_READ(ah, AR_DIAG_SW) &~ AR_DIAG_RX_DIS);
	ar5212EnableMibCounters(ah);
	/* NB: restore current settings if we're not scanning */
	ar5212AniReset(ah, ahp->ah_curchan, ahp->ah_opmode, !is_scanning);
}