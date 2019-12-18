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
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {TYPE_1__* pDataPerXPD; } ;
struct TYPE_4__ {scalar_t__ xpd_gain; scalar_t__* pwr_t4; scalar_t__* pcdac; } ;
typedef  TYPE_2__ EXPN_DATA_PER_CHANNEL_5112 ;

/* Variables and functions */
 int NUM_POINTS_XPD0 ; 
 int NUM_XPD_PER_CHANNEL ; 

__attribute__((used)) static int16_t
ar5112GetMinPower(struct ath_hal *ah, const EXPN_DATA_PER_CHANNEL_5112 *data)
{
	int i, minIndex;
	int16_t minGain,minPwr,minPcdac,retVal;

	/* Assume NUM_POINTS_XPD0 > 0 */
	minGain = data->pDataPerXPD[0].xpd_gain;
	for (minIndex=0,i=1; i<NUM_XPD_PER_CHANNEL; i++) {
		if (data->pDataPerXPD[i].xpd_gain < minGain) {
			minIndex = i;
			minGain = data->pDataPerXPD[i].xpd_gain;
		}
	}
	minPwr = data->pDataPerXPD[minIndex].pwr_t4[0];
	minPcdac = data->pDataPerXPD[minIndex].pcdac[0];
	for (i=1; i<NUM_POINTS_XPD0; i++) {
		if (data->pDataPerXPD[minIndex].pwr_t4[i] < minPwr) {
			minPwr = data->pDataPerXPD[minIndex].pwr_t4[i];
			minPcdac = data->pDataPerXPD[minIndex].pcdac[i];
		}
	}
	retVal = minPwr - (minPcdac*2);
	return(retVal);
}