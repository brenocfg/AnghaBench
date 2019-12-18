#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int halRtsAggrLimit; int halTxStreams; int halRxStreams; void* halHasBBReadWar; void* hal4AddrAggrSupport; void* halMbssidAggrSupport; void* halAutoSleepSupport; void* halUseCombinedRadarRssi; void* halExtChanDfsSupport; void* halRifsTxSupport; void* halRifsRxSupport; void* halCSTSupport; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  void* HAL_BOOL ;

/* Variables and functions */
 void* AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 void* AH_TRUE ; 
 int /*<<< orphan*/  ar5416FillCapabilityInfo (struct ath_hal*) ; 

__attribute__((used)) static HAL_BOOL
ar9160FillCapabilityInfo(struct ath_hal *ah)
{
	HAL_CAPABILITIES *pCap = &AH_PRIVATE(ah)->ah_caps;

	if (!ar5416FillCapabilityInfo(ah))
		return AH_FALSE;
	pCap->halCSTSupport = AH_TRUE;
	pCap->halRifsRxSupport = AH_TRUE;
	pCap->halRifsTxSupport = AH_TRUE;
	pCap->halRtsAggrLimit = 64*1024;	/* 802.11n max */
	pCap->halExtChanDfsSupport = AH_TRUE;
	pCap->halUseCombinedRadarRssi = AH_TRUE;
	pCap->halAutoSleepSupport = AH_FALSE;	/* XXX? */
	pCap->halMbssidAggrSupport = AH_TRUE;
	pCap->hal4AddrAggrSupport = AH_TRUE;
	/* BB Read WAR */
	pCap->halHasBBReadWar = AH_TRUE;

	/* AR9160 is a 2x2 stream device */
	pCap->halTxStreams = 2;
	pCap->halRxStreams = 2;

	return AH_TRUE;
}