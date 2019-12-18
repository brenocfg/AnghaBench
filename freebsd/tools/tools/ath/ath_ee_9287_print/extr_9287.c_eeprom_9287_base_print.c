#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int version; int length; int checksum; int opCapFlags; int eepMisc; int* regDmn; int* macAddr; int rxMask; int txMask; int rfSilent; int blueToothOptions; int deviceCap; int binBuildNumber; int deviceType; int openLoopPwrCntl; int pwrTableOffset; int tempSensSlope; int tempSensSlopePalOn; int* futureBase; } ;
struct TYPE_4__ {TYPE_3__ baseEepHeader; } ;
struct TYPE_5__ {TYPE_1__ ee_base; } ;
typedef  TYPE_2__ HAL_EEPROM_9287 ;
typedef  TYPE_3__ BASE_EEP_9287_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
eeprom_9287_base_print(uint16_t *buf)
{
	HAL_EEPROM_9287 *eep = (HAL_EEPROM_9287 *) buf;
	BASE_EEP_9287_HEADER *eh = &eep->ee_base.baseEepHeader;
	int i;

	printf("| Version: 0x%.4x   | Length: 0x%.4x | Checksum: 0x%.4x ",
	    eh->version, eh->length, eh->checksum);
	printf("| CapFlags: 0x%.2x  | eepMisc: 0x%.2x | RegDomain: 0x%.4x 0x%.4x | \n",
	    eh->opCapFlags, eh->eepMisc, eh->regDmn[0], eh->regDmn[1]);
	printf("| MAC: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x ",
	    eh->macAddr[0], eh->macAddr[1], eh->macAddr[2],
	    eh->macAddr[3], eh->macAddr[4], eh->macAddr[5]);
	printf("| RxMask: 0x%.2x | TxMask: 0x%.2x | RfSilent: 0x%.4x | btOptions: 0x%.4x |\n",
	    eh->rxMask, eh->txMask, eh->rfSilent, eh->blueToothOptions);
	printf("| DeviceCap: 0x%.4x | binBuildNumber: %.8x | deviceType: 0x%.2x | openLoopPwrCntl 0x%.2x |\n",
	    eh->deviceCap, eh->binBuildNumber, eh->deviceType, eh->openLoopPwrCntl);
	printf("| pwrTableOffset: %d | tempSensSlope: %d | tempSensSlopePalOn: %d |\n",
	    eh->pwrTableOffset, eh->tempSensSlope, eh->tempSensSlopePalOn);

	printf("Future:\n");
	for (i = 0; i < sizeof(eh->futureBase) / sizeof(uint16_t); i++) {
		printf("0x%.2x ", eh->futureBase[i]);
	}
	printf("\n");
}