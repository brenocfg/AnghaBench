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
struct ath_hal_5211 {int ah_staId1Defaults; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5211* AH5211 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_ADHOC ; 
 int AR_STA_ID1_DEFAULT_ANTENNA ; 
 int AR_STA_ID1_DESC_ANTENNA ; 
 int AR_STA_ID1_RTS_USE_DEF ; 
 int AR_STA_ID1_STA_AP ; 
#define  HAL_M_HOSTAP 131 
#define  HAL_M_IBSS 130 
#define  HAL_M_MONITOR 129 
#define  HAL_M_STA 128 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5211SetOperatingMode(struct ath_hal *ah, int opmode)
{
	struct ath_hal_5211 *ahp = AH5211(ah);
	uint32_t val;

	val = OS_REG_READ(ah, AR_STA_ID1) & 0xffff;
	switch (opmode) {
	case HAL_M_HOSTAP:
		OS_REG_WRITE(ah, AR_STA_ID1, val
			| AR_STA_ID1_STA_AP
			| AR_STA_ID1_RTS_USE_DEF
			| ahp->ah_staId1Defaults);
		break;
	case HAL_M_IBSS:
		OS_REG_WRITE(ah, AR_STA_ID1, val
			| AR_STA_ID1_ADHOC
			| AR_STA_ID1_DESC_ANTENNA
			| ahp->ah_staId1Defaults);
		break;
	case HAL_M_STA:
	case HAL_M_MONITOR:
		OS_REG_WRITE(ah, AR_STA_ID1, val
			| AR_STA_ID1_DEFAULT_ANTENNA
			| ahp->ah_staId1Defaults);
		break;
	}
}