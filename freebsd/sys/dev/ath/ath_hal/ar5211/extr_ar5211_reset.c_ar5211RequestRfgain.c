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
struct ath_hal_5211 {int /*<<< orphan*/  ah_rfgainState; int /*<<< orphan*/  ah_tx6PowerInHalfDbm; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5211* AH5211 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_PAPD_PROBE ; 
 int AR_PHY_PAPD_PROBE_NEXT_TX ; 
 int /*<<< orphan*/  AR_PHY_PAPD_PROBE_POWERTX ; 
 int /*<<< orphan*/  HAL_RFGAIN_READ_REQUESTED ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar5211RequestRfgain(struct ath_hal *ah)
{
	struct ath_hal_5211 *ahp = AH5211(ah);

	/* Enable the gain readback probe */
	OS_REG_WRITE(ah, AR_PHY_PAPD_PROBE,
		  SM(ahp->ah_tx6PowerInHalfDbm, AR_PHY_PAPD_PROBE_POWERTX)
		| AR_PHY_PAPD_PROBE_NEXT_TX);

	ahp->ah_rfgainState = HAL_RFGAIN_READ_REQUESTED;
}