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
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_MCAST_FIL0 ; 
 int /*<<< orphan*/  AR_MCAST_FIL1 ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

HAL_BOOL
ar5212ClrMulticastFilterIndex(struct ath_hal *ah, uint32_t ix)
{
	uint32_t val;

	if (ix >= 64)
		return AH_FALSE;
	if (ix >= 32) {
		val = OS_REG_READ(ah, AR_MCAST_FIL1);
		OS_REG_WRITE(ah, AR_MCAST_FIL1, (val &~ (1<<(ix-32))));
	} else {
		val = OS_REG_READ(ah, AR_MCAST_FIL0);
		OS_REG_WRITE(ah, AR_MCAST_FIL0, (val &~ (1<<ix)));
	}
	return AH_TRUE;
}