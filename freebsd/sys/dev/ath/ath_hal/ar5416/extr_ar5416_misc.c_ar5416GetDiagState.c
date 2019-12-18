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
struct ath_hal_5416 {int /*<<< orphan*/  ah_hangs; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5416* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int HAL_BB_HANGS ; 
#define  HAL_DIAG_CHECK_HANGS 129 
#define  HAL_DIAG_EEPROM 128 
 int HAL_MAC_HANGS ; 
 int /*<<< orphan*/  ar5212GetDiagState (struct ath_hal*,int,void const*,int,void**,int*) ; 
 int /*<<< orphan*/  ar5416DetectBBHang (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5416DetectMacHang (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_eepromDiag (struct ath_hal*,int,void const*,int,void**,int*) ; 
 scalar_t__ ath_hal_getdiagstate (struct ath_hal*,int,void const*,int,void**,int*) ; 

HAL_BOOL
ar5416GetDiagState(struct ath_hal *ah, int request,
	const void *args, uint32_t argsize,
	void **result, uint32_t *resultsize)
{
	struct ath_hal_5416 *ahp = AH5416(ah);
	int hangs;

	if (ath_hal_getdiagstate(ah, request, args, argsize, result, resultsize))
		return AH_TRUE;
	switch (request) {
	case HAL_DIAG_EEPROM:
		return ath_hal_eepromDiag(ah, request,
		    args, argsize, result, resultsize);
	case HAL_DIAG_CHECK_HANGS:
		if (argsize != sizeof(int))
			return AH_FALSE;
		hangs = *(const int *) args;
		ahp->ah_hangs = 0;
		if (hangs & HAL_BB_HANGS)
			ahp->ah_hangs |= ar5416DetectBBHang(ah);
		/* NB: if BB is hung MAC will be hung too so skip check */
		if (ahp->ah_hangs == 0 && (hangs & HAL_MAC_HANGS))
			ahp->ah_hangs |= ar5416DetectMacHang(ah);
		*result = &ahp->ah_hangs;
		*resultsize = sizeof(ahp->ah_hangs);
		return AH_TRUE;
	}
	return ar5212GetDiagState(ah, request,
	    args, argsize, result, resultsize);
}