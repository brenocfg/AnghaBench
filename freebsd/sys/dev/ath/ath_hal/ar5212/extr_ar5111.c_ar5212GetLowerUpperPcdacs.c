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
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ channelValue; int /*<<< orphan*/  numPcdacValues; int /*<<< orphan*/  PcdacValues; } ;
struct TYPE_4__ {int numChannels; TYPE_2__* pDataPerChannel; } ;
typedef  TYPE_1__ PCDACS_EEPROM ;
typedef  TYPE_2__ DATA_PER_CHANNEL ;

/* Variables and functions */
 int /*<<< orphan*/  ar5212GetLowerUpperValues (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void
ar5212GetLowerUpperPcdacs(uint16_t pcdac, uint16_t channel,
	const PCDACS_EEPROM *pSrcStruct,
	uint16_t *pLowerPcdac, uint16_t *pUpperPcdac)
{
	const DATA_PER_CHANNEL *pChannelData = pSrcStruct->pDataPerChannel;
	int i;

	/* Find the channel information */
	for (i = 0; i < pSrcStruct->numChannels; i++) {
		if (pChannelData->channelValue == channel)
			break;
		pChannelData++;
	}
	ar5212GetLowerUpperValues(pcdac, pChannelData->PcdacValues,
		      pChannelData->numPcdacValues,
		      pLowerPcdac, pUpperPcdac);
}