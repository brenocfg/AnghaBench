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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int const* AH_NULL ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC1 (scalar_t__) ; 
 scalar_t__ AR_KEYTABLE_SIZE ; 
 int AR_KEYTABLE_VALID ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

HAL_BOOL
ar5210SetKeyCacheEntryMac(struct ath_hal *ah, uint16_t entry, const uint8_t *mac)
{
	uint32_t macHi, macLo;

	if (entry < AR_KEYTABLE_SIZE) {
		/*
		 * Set MAC address -- shifted right by 1.  MacLo is
		 * the 4 MSBs, and MacHi is the 2 LSBs.
		 */
		if (mac != AH_NULL) {
			macHi = (mac[5] << 8) | mac[4];
			macLo = (mac[3] << 24)| (mac[2] << 16)
			      | (mac[1] << 8) | mac[0];
			macLo >>= 1;
			macLo |= (macHi & 1) << 31;	/* carry */
			macHi >>= 1;
		} else {
			macLo = macHi = 0;
		}

		OS_REG_WRITE(ah, AR_KEYTABLE_MAC0(entry), macLo);
		OS_REG_WRITE(ah, AR_KEYTABLE_MAC1(entry),
			macHi | AR_KEYTABLE_VALID);
		return AH_TRUE;
	}
	return AH_FALSE;
}