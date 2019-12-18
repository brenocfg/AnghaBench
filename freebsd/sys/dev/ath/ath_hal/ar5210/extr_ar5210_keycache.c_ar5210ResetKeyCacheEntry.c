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
typedef  scalar_t__ uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY1 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY2 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY3 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY4 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC1 (scalar_t__) ; 
 scalar_t__ AR_KEYTABLE_SIZE ; 
 int /*<<< orphan*/  AR_KEYTABLE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5210ResetKeyCacheEntry(struct ath_hal *ah, uint16_t entry)
{
	if (entry < AR_KEYTABLE_SIZE) {
		OS_REG_WRITE(ah, AR_KEYTABLE_KEY0(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_KEY1(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_KEY2(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_KEY3(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_KEY4(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_TYPE(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_MAC0(entry), 0);
		OS_REG_WRITE(ah, AR_KEYTABLE_MAC1(entry), 0);
		return AH_TRUE;
	}
	return AH_FALSE;
}