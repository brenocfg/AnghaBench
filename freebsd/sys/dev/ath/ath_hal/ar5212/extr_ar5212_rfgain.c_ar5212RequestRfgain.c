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
typedef  scalar_t__ uint32_t ;
struct ath_hal_5212 {int /*<<< orphan*/  ah_rfgainState; scalar_t__ ah_txPowerIndexOffset; scalar_t__ ah_ofdmTxPower; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_PAPD_PROBE ; 
 int AR_PHY_PAPD_PROBE_NEXT_TX ; 
 int /*<<< orphan*/  AR_PHY_PAPD_PROBE_POWERTX ; 
 int /*<<< orphan*/  HAL_RFGAIN_READ_REQUESTED ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (scalar_t__,int /*<<< orphan*/ ) ; 

void
ar5212RequestRfgain(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	uint32_t probePowerIndex;

	/* Enable the gain readback probe */
	probePowerIndex = ahp->ah_ofdmTxPower + ahp->ah_txPowerIndexOffset;
	OS_REG_WRITE(ah, AR_PHY_PAPD_PROBE,
		  SM(probePowerIndex, AR_PHY_PAPD_PROBE_POWERTX)
		| AR_PHY_PAPD_PROBE_NEXT_TX);

	ahp->ah_rfgainState = HAL_RFGAIN_READ_REQUESTED;
}