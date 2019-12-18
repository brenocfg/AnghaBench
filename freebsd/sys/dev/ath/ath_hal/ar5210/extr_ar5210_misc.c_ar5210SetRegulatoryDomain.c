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
typedef  scalar_t__ uint16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_currentRD; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_EEP_WRITEPROTECT ; 
 int /*<<< orphan*/  HAL_EEWRITE ; 
 int /*<<< orphan*/  HAL_EINVAL ; 
 int /*<<< orphan*/  HAL_EIO ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5210SetRegulatoryDomain(struct ath_hal *ah,
	uint16_t regDomain, HAL_STATUS *status)
{
	HAL_STATUS ecode;

	if (AH_PRIVATE(ah)->ah_currentRD == regDomain) {
		ecode = HAL_EINVAL;
		goto bad;
	}
	/*
	 * Check if EEPROM is configured to allow this; must
	 * be a proper version and the protection bits must
	 * permit re-writing that segment of the EEPROM.
	 */
	if (ath_hal_eepromGetFlag(ah, AR_EEP_WRITEPROTECT)) {
		ecode = HAL_EEWRITE;
		goto bad;
	}
	ecode = HAL_EIO;		/* disallow all writes */
bad:
	if (status)
		*status = ecode;
	return AH_FALSE;
}