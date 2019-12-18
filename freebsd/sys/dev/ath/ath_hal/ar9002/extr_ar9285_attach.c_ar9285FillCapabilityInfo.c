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
struct TYPE_3__ {int halNumGpioPins; int halTxStreams; int halRxStreams; int halRtsAggrLimit; int halRxStbcSupport; scalar_t__ halTxStbcSupport; void* halPSPollBroken; void* halRxUsingLnaMixing; void* halSpectralScanSupport; void* hal4AddrAggrSupport; void* halMbssidAggrSupport; void* halHasRxSelfLinkedTail; void* hal4kbSplitTransSupport; void* halAutoSleepSupport; void* halBtCoexSupport; void* halUseCombinedRadarRssi; void* halExtChanDfsSupport; void* halRifsTxSupport; void* halRifsRxSupport; void* halCSTSupport; void* halAntDivCombSupport; void* halWowMatchPatternDword; void* halWowMatchPatternExact; void* halWowSupport; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  void* HAL_BOOL ;

/* Variables and functions */
 void* AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 void* AH_TRUE ; 
 scalar_t__ AR_SREV_KITE_12_OR_LATER (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5416FillCapabilityInfo (struct ath_hal*) ; 
 scalar_t__ ar9285_check_div_comb (struct ath_hal*) ; 

__attribute__((used)) static HAL_BOOL
ar9285FillCapabilityInfo(struct ath_hal *ah)
{
	HAL_CAPABILITIES *pCap = &AH_PRIVATE(ah)->ah_caps;

	if (!ar5416FillCapabilityInfo(ah))
		return AH_FALSE;
	pCap->halNumGpioPins = 12;
	pCap->halWowSupport = AH_TRUE;
	pCap->halWowMatchPatternExact = AH_TRUE;
#if 0
	pCap->halWowMatchPatternDword = AH_TRUE;
#endif
	/* AR9285 has 2 antennas but is a 1x1 stream device */
	pCap->halTxStreams = 1;
	pCap->halRxStreams = 1;

	if (ar9285_check_div_comb(ah))
		pCap->halAntDivCombSupport = AH_TRUE;

	pCap->halCSTSupport = AH_TRUE;
	pCap->halRifsRxSupport = AH_TRUE;
	pCap->halRifsTxSupport = AH_TRUE;
	pCap->halRtsAggrLimit = 64*1024;	/* 802.11n max */
	pCap->halExtChanDfsSupport = AH_TRUE;
	pCap->halUseCombinedRadarRssi = AH_TRUE;
#if 1
	/* XXX bluetooth */
	pCap->halBtCoexSupport = AH_TRUE;
#endif
	pCap->halAutoSleepSupport = AH_FALSE;	/* XXX? */
	pCap->hal4kbSplitTransSupport = AH_FALSE;
	/* Disable this so Block-ACK works correctly */
	pCap->halHasRxSelfLinkedTail = AH_FALSE;
	pCap->halMbssidAggrSupport = AH_TRUE;  
	pCap->hal4AddrAggrSupport = AH_TRUE;
	pCap->halSpectralScanSupport = AH_TRUE;
	pCap->halRxUsingLnaMixing = AH_TRUE;

	if (AR_SREV_KITE_12_OR_LATER(ah))
		pCap->halPSPollBroken = AH_FALSE;

	/* Only RX STBC supported */
	pCap->halRxStbcSupport = 1;
	pCap->halTxStbcSupport = 0;

	return AH_TRUE;
}