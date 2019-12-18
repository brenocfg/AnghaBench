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
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int int16_t ;
struct TYPE_5__ {TYPE_1__* pDataPerPDGain; } ;
struct TYPE_4__ {int numVpd; int* pwr_t4; int* Vpd; } ;
typedef  TYPE_2__ RAW_DATA_PER_CHANNEL_2317 ;

/* Variables and functions */
 size_t MAX_NUM_PDGAINS_PER_CHANNEL ; 

__attribute__((used)) static int16_t
ar2317GetMaxPower(struct ath_hal *ah, const RAW_DATA_PER_CHANNEL_2317 *data)
{
	uint32_t ii;
	uint16_t Pmax=0,numVpd;
	uint16_t vpdmax;
	
	for (ii=0; ii< MAX_NUM_PDGAINS_PER_CHANNEL; ii++) {
		/* work forwards cuase lowest pdGain for highest power */
		numVpd = data->pDataPerPDGain[ii].numVpd;
		if (numVpd > 0) {
			Pmax = data->pDataPerPDGain[ii].pwr_t4[numVpd-1];
			vpdmax = data->pDataPerPDGain[ii].Vpd[numVpd-1];
			return(Pmax);
		}
	}
	return(Pmax);
}