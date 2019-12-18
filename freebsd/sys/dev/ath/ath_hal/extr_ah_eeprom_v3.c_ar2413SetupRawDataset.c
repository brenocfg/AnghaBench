#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_10__ {int numChannels; int* pChannels; } ;
struct TYPE_9__ {int numChannels; int xpd_mask; int* pChannels; TYPE_2__* pDataPerChannel; } ;
struct TYPE_8__ {int channelValue; int numPdGains; TYPE_1__* pDataPerPDGain; } ;
struct TYPE_7__ {int pd_gain; scalar_t__ numVpd; } ;
typedef  TYPE_3__ RAW_DATA_STRUCT_2413 ;
typedef  TYPE_4__ EEPROM_DATA_STRUCT_2413 ;

/* Variables and functions */
 int MAX_NUM_PDGAINS_PER_CHANNEL ; 
 scalar_t__ NUM_POINTS_LAST_PDGAIN ; 
 scalar_t__ NUM_POINTS_OTHER_PDGAINS ; 

__attribute__((used)) static void
ar2413SetupRawDataset(RAW_DATA_STRUCT_2413 *pRaw, EEPROM_DATA_STRUCT_2413 *pCal)
{
	uint16_t i, j, kk, channelValue;
	uint16_t xpd_mask;
	uint16_t numPdGainsUsed;

	pRaw->numChannels = pCal->numChannels;

	xpd_mask = pRaw->xpd_mask;
	numPdGainsUsed = 0;
	if ((xpd_mask >> 0) & 0x1) numPdGainsUsed++;
	if ((xpd_mask >> 1) & 0x1) numPdGainsUsed++;
	if ((xpd_mask >> 2) & 0x1) numPdGainsUsed++;
	if ((xpd_mask >> 3) & 0x1) numPdGainsUsed++;

	for (i = 0; i < pCal->numChannels; i++) {
		channelValue = pCal->pChannels[i];

		pRaw->pChannels[i] = channelValue;

		pRaw->pDataPerChannel[i].channelValue = channelValue;
		pRaw->pDataPerChannel[i].numPdGains = numPdGainsUsed;

		kk = 0;
		for (j = 0; j < MAX_NUM_PDGAINS_PER_CHANNEL; j++) {
			pRaw->pDataPerChannel[i].pDataPerPDGain[j].pd_gain = j;
			if ((xpd_mask >> j) & 0x1) {
				pRaw->pDataPerChannel[i].pDataPerPDGain[j].numVpd = NUM_POINTS_OTHER_PDGAINS;
				kk++;
				if (kk == 1) {
					/* 
					 * lowest pd_gain corresponds
					 *  to highest power and thus,
					 *  has one more point
					 */
					pRaw->pDataPerChannel[i].pDataPerPDGain[j].numVpd = NUM_POINTS_LAST_PDGAIN;
				}
			} else {
				pRaw->pDataPerChannel[i].pDataPerPDGain[j].numVpd = 0;
			}
		}
	}
}