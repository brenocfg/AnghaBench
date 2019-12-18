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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ah_eeprom; } ;
typedef  int /*<<< orphan*/  HAL_EEPROM_v14 ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
#define  HAL_DIAG_EEPROM 128 

__attribute__((used)) static HAL_BOOL
v14EepromDiag(struct ath_hal *ah, int request,
     const void *args, uint32_t argsize, void **result, uint32_t *resultsize)
{
	HAL_EEPROM_v14 *ee = AH_PRIVATE(ah)->ah_eeprom;

	switch (request) {
	case HAL_DIAG_EEPROM:
		*result = ee;
		*resultsize = sizeof(HAL_EEPROM_v14);
		return AH_TRUE;
	}
	return AH_FALSE;
}