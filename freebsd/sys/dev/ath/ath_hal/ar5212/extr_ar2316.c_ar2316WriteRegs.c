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
typedef  int u_int ;
struct ath_hal_5212 {scalar_t__ ah_cwCalRequire; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 scalar_t__ AH_FALSE ; 
 int /*<<< orphan*/  HAL_INI_WRITE_ARRAY (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 int OS_REG_READ (struct ath_hal*,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int,int) ; 
 int /*<<< orphan*/  ar5212BB_RfGain_2316 ; 
 int /*<<< orphan*/  ar5212Common_2316 ; 
 int /*<<< orphan*/  ar5212Modes_2316 ; 

__attribute__((used)) static void
ar2316WriteRegs(struct ath_hal *ah, u_int modesIndex, u_int freqIndex,
	int regWrites)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	HAL_INI_WRITE_ARRAY(ah, ar5212Modes_2316, modesIndex, regWrites);
	HAL_INI_WRITE_ARRAY(ah, ar5212Common_2316, 1, regWrites);
	HAL_INI_WRITE_ARRAY(ah, ar5212BB_RfGain_2316, freqIndex, regWrites);

	/* For AP51 */
        if (!ahp->ah_cwCalRequire) {
		OS_REG_WRITE(ah, 0xa358, (OS_REG_READ(ah, 0xa358) & ~0x2));
        } else {
		ahp->ah_cwCalRequire = AH_FALSE;
        }
}