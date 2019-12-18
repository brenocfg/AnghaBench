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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_5__ {size_t numChannels; int xpd_mask; size_t* pChannels; TYPE_1__* pDataPerChannel; } ;
struct TYPE_4__ {size_t channelValue; size_t numPdGains; } ;
typedef  TYPE_2__ EEPROM_DATA_STRUCT_2413 ;

/* Variables and functions */

__attribute__((used)) static void
ar2413SetupEEPROMDataset(EEPROM_DATA_STRUCT_2413 *pEEPROMDataset2413,
	uint16_t myNumRawChannels, uint16_t *pMyRawChanList)
{
	uint16_t i, channelValue;
	uint32_t xpd_mask;
	uint16_t numPdGainsUsed;

	pEEPROMDataset2413->numChannels = myNumRawChannels;

	xpd_mask = pEEPROMDataset2413->xpd_mask;
	numPdGainsUsed = 0;
	if ((xpd_mask >> 0) & 0x1) numPdGainsUsed++;
	if ((xpd_mask >> 1) & 0x1) numPdGainsUsed++;
	if ((xpd_mask >> 2) & 0x1) numPdGainsUsed++;
	if ((xpd_mask >> 3) & 0x1) numPdGainsUsed++;

	for (i = 0; i < myNumRawChannels; i++) {
		channelValue = pMyRawChanList[i];
		pEEPROMDataset2413->pChannels[i] = channelValue;
		pEEPROMDataset2413->pDataPerChannel[i].channelValue = channelValue;
		pEEPROMDataset2413->pDataPerChannel[i].numPdGains = numPdGainsUsed;
	}
}