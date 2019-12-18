#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ath_hal {int dummy; } ;
struct ar531x_boarddata {int /*<<< orphan*/ * wlan1Mac; int /*<<< orphan*/ * wlan0Mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_macaddr; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 struct ar531x_boarddata* AR5312_BOARDCONFIG (struct ath_hal*) ; 
 int AR5312_UNIT (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,int) ; 

__attribute__((used)) static HAL_BOOL
ar5312GetMacAddr(struct ath_hal *ah)
{
	const struct ar531x_boarddata *board = AR5312_BOARDCONFIG(ah); 
        int wlanNum = AR5312_UNIT(ah);
        const uint8_t *macAddr;

	switch (wlanNum) {
	case 0:
		macAddr = board->wlan0Mac;
		break;
	case 1:
		macAddr = board->wlan1Mac;
		break;
	default:
#ifdef AH_DEBUG
		ath_hal_printf(ah, "Invalid WLAN wmac index (%d)\n",
			       wlanNum);
#endif
		return AH_FALSE;
	}
	OS_MEMCPY(AH5212(ah)->ah_macaddr, macAddr, 6);
	return AH_TRUE;
}