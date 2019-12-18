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
struct ath_hal_5212 {int /*<<< orphan*/  ah_mibStats; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHYCNTMASK1 ; 
 int /*<<< orphan*/  AR_PHYCNTMASK2 ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_DEBUG_ANI ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5212DisableMibCounters (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5212UpdateMibCounters (struct ath_hal*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
disableAniMIBCounters(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	HALDEBUG(ah, HAL_DEBUG_ANI, "Disable MIB counters\n");

	ar5212UpdateMibCounters(ah, &ahp->ah_mibStats);	/* save stats */
	ar5212DisableMibCounters(ah);			/* disable everything */

	OS_REG_WRITE(ah, AR_PHYCNTMASK1, 0);
	OS_REG_WRITE(ah, AR_PHYCNTMASK2, 0);
}