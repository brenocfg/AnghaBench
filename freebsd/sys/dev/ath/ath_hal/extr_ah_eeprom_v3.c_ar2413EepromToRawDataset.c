#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int int16_t ;
struct TYPE_12__ {int* pwr_I; int* Vpd_I; int** pwr_delta_t2; int** Vpd_delta; int /*<<< orphan*/  channelValue; } ;
struct TYPE_11__ {scalar_t__ xpd_mask; int numChannels; TYPE_5__* pDataPerChannel; } ;
struct TYPE_10__ {int numVpd; int* pwr_t4; int* Vpd; } ;
struct TYPE_9__ {scalar_t__ xpd_mask; int numChannels; TYPE_1__* pDataPerChannel; } ;
struct TYPE_8__ {TYPE_3__* pDataPerPDGain; int /*<<< orphan*/  channelValue; } ;
typedef  TYPE_2__ RAW_DATA_STRUCT_2413 ;
typedef  TYPE_3__ RAW_DATA_PER_PDGAIN_2413 ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  TYPE_4__ EEPROM_DATA_STRUCT_2413 ;
typedef  TYPE_5__ EEPROM_DATA_PER_CHANNEL_2413 ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int MAX_NUM_PDGAINS_PER_CHANNEL ; 

__attribute__((used)) static HAL_BOOL
ar2413EepromToRawDataset(struct ath_hal *ah,
	EEPROM_DATA_STRUCT_2413 *pCal, RAW_DATA_STRUCT_2413 *pRaw)
{
	uint16_t ii, jj, kk, ss;
	RAW_DATA_PER_PDGAIN_2413 *pRawXPD;
	/* ptr to array of info held per channel */
	EEPROM_DATA_PER_CHANNEL_2413 *pCalCh;
	uint16_t xgain_list[MAX_NUM_PDGAINS_PER_CHANNEL];
	uint16_t xpd_mask;
	uint32_t numPdGainsUsed;

	HALASSERT(pRaw->xpd_mask == pCal->xpd_mask);

	xgain_list[0] = 0xDEAD;
	xgain_list[1] = 0xDEAD;
	xgain_list[2] = 0xDEAD;
	xgain_list[3] = 0xDEAD;

	numPdGainsUsed = 0;
	xpd_mask = pRaw->xpd_mask;
	for (jj = 0; jj < MAX_NUM_PDGAINS_PER_CHANNEL; jj++) {
		if ((xpd_mask >> (MAX_NUM_PDGAINS_PER_CHANNEL-jj-1)) & 1)
			xgain_list[numPdGainsUsed++] = MAX_NUM_PDGAINS_PER_CHANNEL-jj-1;
	}

	pRaw->numChannels = pCal->numChannels;
	for (ii = 0; ii < pRaw->numChannels; ii++) {
		pCalCh = &(pCal->pDataPerChannel[ii]);
		pRaw->pDataPerChannel[ii].channelValue = pCalCh->channelValue;

		/* numVpd has already been setup appropriately for the relevant pdGains */
		for (jj = 0; jj < numPdGainsUsed; jj++) {
			/* use jj for calDataset and ss for rawDataset */
			ss = xgain_list[jj];
			pRawXPD = &(pRaw->pDataPerChannel[ii].pDataPerPDGain[ss]);
			HALASSERT(pRawXPD->numVpd >= 1);

			pRawXPD->pwr_t4[0] = (uint16_t)(4*pCalCh->pwr_I[jj]);
			pRawXPD->Vpd[0]    = pCalCh->Vpd_I[jj];

			for (kk = 1; kk < pRawXPD->numVpd; kk++) {
				pRawXPD->pwr_t4[kk] = (int16_t)(pRawXPD->pwr_t4[kk-1] + 2*pCalCh->pwr_delta_t2[kk-1][jj]);
				pRawXPD->Vpd[kk] = (uint16_t)(pRawXPD->Vpd[kk-1] + pCalCh->Vpd_delta[kk-1][jj]);
			}
			/* loop over Vpds */
		}
		/* loop over pd_gains */
	}
	/* loop over channels */
	return AH_TRUE;
}