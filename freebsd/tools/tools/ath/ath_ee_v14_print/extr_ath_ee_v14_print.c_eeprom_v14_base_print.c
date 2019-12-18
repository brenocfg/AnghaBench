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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int version; int length; int checksum; int opCapFlags; int eepMisc; int* regDmn; int* macAddr; int rxMask; int txMask; int rfSilent; int blueToothOptions; int deviceCap; int binBuildNumber; int deviceType; scalar_t__* futureBase; scalar_t__ frac_n_5g; scalar_t__ pwr_table_offset; scalar_t__ desiredScaleCCK; scalar_t__ rcChainMask; scalar_t__ txGainType; scalar_t__ dacLpMode; scalar_t__ openLoopPwrCntl; scalar_t__ dacHiPwrMode_5G; scalar_t__ rxGainType; scalar_t__ divChain; scalar_t__ fastClk5g; scalar_t__ pwdclkind; } ;
struct TYPE_4__ {TYPE_3__ baseEepHeader; } ;
struct TYPE_5__ {int* ee_antennaGainMax; TYPE_1__ ee_base; } ;
typedef  TYPE_2__ HAL_EEPROM_v14 ;
typedef  TYPE_3__ BASE_EEP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
eeprom_v14_base_print(uint16_t *buf)
{
	HAL_EEPROM_v14 *eep = (HAL_EEPROM_v14 *) buf;
	BASE_EEP_HEADER *eh = &eep->ee_base.baseEepHeader;
	int i;

	printf("| Version: 0x%.4x   | Length: 0x%.4x | Checksum: 0x%.4x ",
	    eh->version, eh->length, eh->checksum);
	printf("| CapFlags: 0x%.2x\n", eh->opCapFlags);

	printf("| eepMisc: 0x%.2x | RegDomain: 0x%.4x 0x%.4x | \n",
	    eh->eepMisc, eh->regDmn[0], eh->regDmn[1]);
	printf("| MAC: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x ",
	    eh->macAddr[0], eh->macAddr[1], eh->macAddr[2],
	    eh->macAddr[3], eh->macAddr[4], eh->macAddr[5]);
	printf("| RxMask: 0x%.2x | TxMask: 0x%.2x | RfSilent: 0x%.4x | btOptions: 0x%.4x |\n",
	    eh->rxMask, eh->txMask, eh->rfSilent, eh->blueToothOptions);
	printf("| DeviceCap: 0x%.4x | binBuildNumber: %.8x | deviceType: 0x%.2x |\n",
	    eh->deviceCap, eh->binBuildNumber, eh->deviceType);

	printf("| pwdclkind: 0x%.2x | fastClk5g: 0x%.2x | divChain: 0x%.2x | rxGainType: 0x%.2x |\n",
	    (int) eh->pwdclkind, (int) eh->fastClk5g, (int) eh->divChain,
	    (int) eh->rxGainType);

	printf("| dacHiPwrMode_5G: 0x%.2x | openLoopPwrCntl: 0x%.2x | dacLpMode: 0x%.2x\n",
	    (int) eh->dacHiPwrMode_5G, (int) eh->openLoopPwrCntl, (int) eh->dacLpMode);
	printf("| txGainType: 0x%.2x | rcChainMask: 0x%.2x |\n",
	    (int) eh->txGainType, (int) eh->rcChainMask);

	printf("| desiredScaleCCK: 0x%.2x | pwr_table_offset: 0x%.2x | frac_n_5g: %.2x\n",
	    (int) eh->desiredScaleCCK, (int) eh->pwr_table_offset, (int) eh->frac_n_5g);

	/* because it's convienent */
	printf("| antennaGainMax[0]: 0x%.2x antennaGainMax[1]: 0x%.2x |\n",
	    eep->ee_antennaGainMax[0], eep->ee_antennaGainMax[1]);

	printf(" | futureBase:");
	for (i = 0; i < sizeof(eh->futureBase) / sizeof(uint8_t); i++) 
		printf(" %.2x", (int) eh->futureBase[i]);
	printf("\n");
}