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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {TYPE_1__* pDataPerPDGain; } ;
struct TYPE_4__ {scalar_t__ numVpd; scalar_t__* pwr_t4; } ;
typedef  TYPE_2__ RAW_DATA_PER_CHANNEL_2413 ;

/* Variables and functions */
 scalar_t__ MAX_NUM_PDGAINS_PER_CHANNEL ; 

__attribute__((used)) static int16_t
ar2413GetMinPower(struct ath_hal *ah, const RAW_DATA_PER_CHANNEL_2413 *data)
{
	uint32_t ii,jj;
	uint16_t Pmin=0,numVpd;

	for (ii = 0; ii < MAX_NUM_PDGAINS_PER_CHANNEL; ii++) {
		jj = MAX_NUM_PDGAINS_PER_CHANNEL - ii - 1;
		/* work backwards 'cause highest pdGain for lowest power */
		numVpd = data->pDataPerPDGain[jj].numVpd;
		if (numVpd > 0) {
			Pmin = data->pDataPerPDGain[jj].pwr_t4[0];
			return(Pmin);
		}
	}
	return(Pmin);
}