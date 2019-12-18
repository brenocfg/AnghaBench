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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {TYPE_1__* pDataPerPDGain; } ;
struct TYPE_4__ {int numVpd; int /*<<< orphan*/ * pwr_t4; } ;
typedef  TYPE_2__ RAW_DATA_PER_CHANNEL_2413 ;

/* Variables and functions */
 size_t MAX_NUM_PDGAINS_PER_CHANNEL ; 

__attribute__((used)) static int16_t
getMaxPowerV5(const RAW_DATA_PER_CHANNEL_2413 *data)
{
	uint32_t i;
	uint16_t numVpd;

	for (i = 0; i < MAX_NUM_PDGAINS_PER_CHANNEL; i++) {
		numVpd = data->pDataPerPDGain[i].numVpd;
		if (numVpd > 0)
			return data->pDataPerPDGain[i].pwr_t4[numVpd-1];
	}
	return 0;
}