#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_4__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_3__ {int /*<<< orphan*/  ee_antennaGainMax; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  TYPE_1__ HAL_EEPROM_v4k ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
#define  AR_EEP_ANTGAINMAX_2 128 
 int /*<<< orphan*/  HAL_EINVAL ; 
 int /*<<< orphan*/  HAL_OK ; 

__attribute__((used)) static HAL_STATUS
v4kEepromSet(struct ath_hal *ah, int param, int v)
{
	HAL_EEPROM_v4k *ee = AH_PRIVATE(ah)->ah_eeprom;

	switch (param) {
	case AR_EEP_ANTGAINMAX_2:
		ee->ee_antennaGainMax = (int8_t) v;
		return HAL_OK;
	}
	return HAL_EINVAL;
}