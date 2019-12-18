#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_5__ {void* pChannels; } ;
struct TYPE_4__ {TYPE_2__* ee_modePowerArray5112; } ;
typedef  TYPE_1__ HAL_EEPROM ;
typedef  TYPE_2__ EEPROM_POWER_EXPN_5112 ;

/* Variables and functions */
 void* AH_NULL ; 
 int /*<<< orphan*/  ath_hal_free (void*) ; 
 int headerInfo11A ; 
 int headerInfo11G ; 

__attribute__((used)) static void
freeEepromRawPowerCalInfo5112(struct ath_hal *ah, HAL_EEPROM *ee)
{
	int mode;
	void *data;

	for (mode = headerInfo11A; mode <= headerInfo11G; mode++) {
		EEPROM_POWER_EXPN_5112 *pPowerExpn =
			&ee->ee_modePowerArray5112[mode];
		data = pPowerExpn->pChannels;
		if (data != AH_NULL) {
			pPowerExpn->pChannels = AH_NULL;
			ath_hal_free(data);
		}
	}
}