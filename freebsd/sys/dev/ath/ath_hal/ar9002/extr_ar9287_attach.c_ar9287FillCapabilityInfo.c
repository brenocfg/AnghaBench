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
struct TYPE_3__ {int halNumGpioPins; int halRtsAggrLimit; int halRxStbcSupport; int halTxStbcSupport; int halHTSGI20Support; void* halEnhancedDfsSupport; void* halSpectralScanSupport; void* halPSPollBroken; void* halHasRxSelfLinkedTail; void* hal4kbSplitTransSupport; void* halAutoSleepSupport; void* halBtCoexSupport; void* halUseCombinedRadarRssi; void* halExtChanDfsSupport; void* halRifsTxSupport; void* halRifsRxSupport; void* halCSTSupport; void* halWowMatchPatternDword; void* halWowMatchPatternExact; void* halWowSupport; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  void* HAL_BOOL ;

/* Variables and functions */
 void* AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 void* AH_TRUE ; 
 int /*<<< orphan*/  ar5416FillCapabilityInfo (struct ath_hal*) ; 

__attribute__((used)) static HAL_BOOL
ar9287FillCapabilityInfo(struct ath_hal *ah)
{
	HAL_CAPABILITIES *pCap = &AH_PRIVATE(ah)->ah_caps;

	if (!ar5416FillCapabilityInfo(ah))
		return AH_FALSE;
	pCap->halNumGpioPins = 10;
	pCap->halWowSupport = AH_TRUE;
	pCap->halWowMatchPatternExact = AH_TRUE;
#if 0
	pCap->halWowMatchPatternDword = AH_TRUE;
#endif

	pCap->halCSTSupport = AH_TRUE;
	pCap->halRifsRxSupport = AH_TRUE;
	pCap->halRifsTxSupport = AH_TRUE;
	pCap->halRtsAggrLimit = 64*1024;	/* 802.11n max */
	pCap->halExtChanDfsSupport = AH_TRUE;
	pCap->halUseCombinedRadarRssi = AH_TRUE;
#if 0
	/* XXX bluetooth */
	pCap->halBtCoexSupport = AH_TRUE;
#endif
	pCap->halAutoSleepSupport = AH_FALSE;	/* XXX? */
	pCap->hal4kbSplitTransSupport = AH_FALSE;
	/* Disable this so Block-ACK works correctly */
	pCap->halHasRxSelfLinkedTail = AH_FALSE;
	pCap->halPSPollBroken = AH_FALSE;
	pCap->halSpectralScanSupport = AH_TRUE;

	/* Hardware supports (at least) single-stream STBC TX/RX */
	pCap->halRxStbcSupport = 1;
	pCap->halTxStbcSupport = 1;

	/* Hardware supports short-GI w/ 20MHz */
	pCap->halHTSGI20Support = 1;

	pCap->halEnhancedDfsSupport = AH_TRUE;

	return AH_TRUE;
}