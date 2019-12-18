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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  halTxTstampPrecision; int /*<<< orphan*/  halRxDoMyBeacon; int /*<<< orphan*/  halRxUsingLnaMixing; int /*<<< orphan*/  halMfpSupport; int /*<<< orphan*/  halSerialiseRegWar; int /*<<< orphan*/  halHasBBReadWar; int /*<<< orphan*/  halHasRxSelfLinkedTail; int /*<<< orphan*/  halRxStreams; int /*<<< orphan*/  halTxStreams; int /*<<< orphan*/  halBssidMatchSupport; int /*<<< orphan*/  halIntrMask; int /*<<< orphan*/  halEnhancedDfsSupport; int /*<<< orphan*/  halAntDivCombSupport; int /*<<< orphan*/  halRxTstampPrecision; int /*<<< orphan*/  halHTSGI20Support; int /*<<< orphan*/  halSpectralScanSupport; int /*<<< orphan*/  halBtCoexSupport; int /*<<< orphan*/  halNumMRRetries; int /*<<< orphan*/  halRxLpFifoDepth; int /*<<< orphan*/  halRxHpFifoDepth; int /*<<< orphan*/  halRxStatusLen; int /*<<< orphan*/  halTxStatusLen; int /*<<< orphan*/  halTxDescLen; int /*<<< orphan*/  halNumTxMaps; int /*<<< orphan*/  halEnhancedDmaSupport; int /*<<< orphan*/  hal4kbSplitTransSupport; int /*<<< orphan*/  halMbssidAggrSupport; int /*<<< orphan*/  halAutoSleepSupport; int /*<<< orphan*/  halUseCombinedRadarRssi; int /*<<< orphan*/  halTxStbcSupport; int /*<<< orphan*/  halRxStbcSupport; int /*<<< orphan*/  halExtChanDfsSupport; int /*<<< orphan*/  hal4AddrAggrSupport; int /*<<< orphan*/  halRtsAggrLimit; int /*<<< orphan*/  halCSTSupport; int /*<<< orphan*/  halNumGpioPins; int /*<<< orphan*/  halRxChainMask; int /*<<< orphan*/  halTxChainMask; int /*<<< orphan*/  halFastCCSupport; int /*<<< orphan*/  halGTTSupport; int /*<<< orphan*/  halHTSupport; int /*<<< orphan*/  halRfSilentSupport; int /*<<< orphan*/  halMcastKeySrchSupport; int /*<<< orphan*/  halBssIdMaskSupport; int /*<<< orphan*/  halFastFramesSupport; int /*<<< orphan*/  halBurstSupport; int /*<<< orphan*/  halCompressSupport; int /*<<< orphan*/  halPSPollBroken; int /*<<< orphan*/  halVEOLSupport; int /*<<< orphan*/  halTotalQueues; int /*<<< orphan*/  halKeyCacheSize; int /*<<< orphan*/  halHwPhyCounterSupport; } ;
struct TYPE_4__ {int /*<<< orphan*/  ah_rxornIsFatal; int /*<<< orphan*/  ah_currentRDext; int /*<<< orphan*/  ah_rfsilent; int /*<<< orphan*/  ah_rfkillEnabled; int /*<<< orphan*/  ah_tpScale; int /*<<< orphan*/  ah_maxPowerLevel; int /*<<< orphan*/  ah_powerLimit; int /*<<< orphan*/  ah_diagreg; int /*<<< orphan*/  ah_dfsDomain; int /*<<< orphan*/  ah_currentRD; TYPE_1__ ah_caps; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_CAPABILITY_TYPE ;
typedef  TYPE_1__ HAL_CAPABILITIES ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
#define  HAL_CAP_11D 193 
#define  HAL_CAP_4ADDR_AGGR 192 
#define  HAL_CAP_ANT_DIV_COMB 191 
#define  HAL_CAP_AUTO_SLEEP 190 
#define  HAL_CAP_BB_READ_WAR 189 
#define  HAL_CAP_BSSIDMASK 188 
#define  HAL_CAP_BSSIDMATCH 187 
#define  HAL_CAP_BT_COEX 186 
#define  HAL_CAP_BURST 185 
#define  HAL_CAP_CIPHER 184 
#define  HAL_CAP_COMBINED_RADAR_RSSI 183 
#define  HAL_CAP_COMPRESSION 182 
#define  HAL_CAP_CST 181 
#define  HAL_CAP_DFS_DMN 180 
#define  HAL_CAP_DIAG 179 
#define  HAL_CAP_DIVERSITY 178 
#define  HAL_CAP_DO_MYBEACON 177 
#define  HAL_CAP_ENHANCED_DFS_SUPPORT 176 
#define  HAL_CAP_ENHANCED_DMA_SUPPORT 175 
#define  HAL_CAP_EXT_CHAN_DFS 174 
#define  HAL_CAP_FASTFRAME 173 
#define  HAL_CAP_FAST_CC 172 
#define  HAL_CAP_GTXTO 171 
#define  HAL_CAP_HT 170 
#define  HAL_CAP_HT20_SGI 169 
#define  HAL_CAP_INTRMASK 168 
#define  HAL_CAP_KEYCACHE_SIZE 167 
#define  HAL_CAP_MBSSID_AGGR_SUPPORT 166 
#define  HAL_CAP_MCAST_KEYSRCH 165 
#define  HAL_CAP_MFP 164 
#define  HAL_CAP_NUM_GPIO_PINS 163 
#define  HAL_CAP_NUM_MR_RETRIES 162 
#define  HAL_CAP_NUM_TXMAPS 161 
#define  HAL_CAP_NUM_TXQUEUES 160 
#define  HAL_CAP_PHYCOUNTERS 159 
#define  HAL_CAP_PSPOLL 158 
#define  HAL_CAP_REG_DMN 157 
#define  HAL_CAP_REG_FLAG 156 
#define  HAL_CAP_RFSILENT 155 
#define  HAL_CAP_RTS_AGGR_LIMIT 154 
#define  HAL_CAP_RXBUFSIZE 153 
#define  HAL_CAP_RXDESC_SELFLINK 152 
#define  HAL_CAP_RXFIFODEPTH 151 
#define  HAL_CAP_RXORN_FATAL 150 
#define  HAL_CAP_RXSTATUSLEN 149 
#define  HAL_CAP_RXTSTAMP_PREC 148 
#define  HAL_CAP_RX_CHAINMASK 147 
#define  HAL_CAP_RX_LNA_MIXING 146 
#define  HAL_CAP_RX_STBC 145 
#define  HAL_CAP_SERIALISE_WAR 144 
#define  HAL_CAP_SPECTRAL_SCAN 143 
#define  HAL_CAP_SPLIT_4KB_TRANS 142 
#define  HAL_CAP_STREAMS 141 
#define  HAL_CAP_TKIP_MIC 140 
#define  HAL_CAP_TKIP_SPLIT 139 
#define  HAL_CAP_TSF_ADJUST 138 
#define  HAL_CAP_TXDESCLEN 137 
#define  HAL_CAP_TXPOW 136 
#define  HAL_CAP_TXSTATUSLEN 135 
#define  HAL_CAP_TXTSTAMP_PREC 134 
#define  HAL_CAP_TX_CHAINMASK 133 
#define  HAL_CAP_TX_STBC 132 
#define  HAL_CAP_VEOL 131 
#define  HAL_CAP_WME_TKIPMIC 130 
 int /*<<< orphan*/  HAL_EINVAL ; 
 int /*<<< orphan*/  HAL_ENOTSUPP ; 
 int /*<<< orphan*/  HAL_ENXIO ; 
 int /*<<< orphan*/  HAL_OK ; 
#define  HAL_RX_QUEUE_HP 129 
#define  HAL_RX_QUEUE_LP 128 

HAL_STATUS
ath_hal_getcapability(struct ath_hal *ah, HAL_CAPABILITY_TYPE type,
	uint32_t capability, uint32_t *result)
{
	const HAL_CAPABILITIES *pCap = &AH_PRIVATE(ah)->ah_caps;

	switch (type) {
	case HAL_CAP_REG_DMN:		/* regulatory domain */
		*result = AH_PRIVATE(ah)->ah_currentRD;
		return HAL_OK;
	case HAL_CAP_DFS_DMN:		/* DFS Domain */
		*result = AH_PRIVATE(ah)->ah_dfsDomain;
		return HAL_OK;
	case HAL_CAP_CIPHER:		/* cipher handled in hardware */
	case HAL_CAP_TKIP_MIC:		/* handle TKIP MIC in hardware */
		return HAL_ENOTSUPP;
	case HAL_CAP_TKIP_SPLIT:	/* hardware TKIP uses split keys */
		return HAL_ENOTSUPP;
	case HAL_CAP_PHYCOUNTERS:	/* hardware PHY error counters */
		return pCap->halHwPhyCounterSupport ? HAL_OK : HAL_ENXIO;
	case HAL_CAP_WME_TKIPMIC:   /* hardware can do TKIP MIC when WMM is turned on */
		return HAL_ENOTSUPP;
	case HAL_CAP_DIVERSITY:		/* hardware supports fast diversity */
		return HAL_ENOTSUPP;
	case HAL_CAP_KEYCACHE_SIZE:	/* hardware key cache size */
		*result =  pCap->halKeyCacheSize;
		return HAL_OK;
	case HAL_CAP_NUM_TXQUEUES:	/* number of hardware tx queues */
		*result = pCap->halTotalQueues;
		return HAL_OK;
	case HAL_CAP_VEOL:		/* hardware supports virtual EOL */
		return pCap->halVEOLSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_PSPOLL:		/* hardware PS-Poll support works */
		return pCap->halPSPollBroken ? HAL_ENOTSUPP : HAL_OK;
	case HAL_CAP_COMPRESSION:
		return pCap->halCompressSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_BURST:
		return pCap->halBurstSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_FASTFRAME:
		return pCap->halFastFramesSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_DIAG:		/* hardware diagnostic support */
		*result = AH_PRIVATE(ah)->ah_diagreg;
		return HAL_OK;
	case HAL_CAP_TXPOW:		/* global tx power limit  */
		switch (capability) {
		case 0:			/* facility is supported */
			return HAL_OK;
		case 1:			/* current limit */
			*result = AH_PRIVATE(ah)->ah_powerLimit;
			return HAL_OK;
		case 2:			/* current max tx power */
			*result = AH_PRIVATE(ah)->ah_maxPowerLevel;
			return HAL_OK;
		case 3:			/* scale factor */
			*result = AH_PRIVATE(ah)->ah_tpScale;
			return HAL_OK;
		}
		return HAL_ENOTSUPP;
	case HAL_CAP_BSSIDMASK:		/* hardware supports bssid mask */
		return pCap->halBssIdMaskSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_MCAST_KEYSRCH:	/* multicast frame keycache search */
		return pCap->halMcastKeySrchSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_TSF_ADJUST:	/* hardware has beacon tsf adjust */
		return HAL_ENOTSUPP;
	case HAL_CAP_RFSILENT:		/* rfsilent support  */
		switch (capability) {
		case 0:			/* facility is supported */
			return pCap->halRfSilentSupport ? HAL_OK : HAL_ENOTSUPP;
		case 1:			/* current setting */
			return AH_PRIVATE(ah)->ah_rfkillEnabled ?
				HAL_OK : HAL_ENOTSUPP;
		case 2:			/* rfsilent config */
			*result = AH_PRIVATE(ah)->ah_rfsilent;
			return HAL_OK;
		}
		return HAL_ENOTSUPP;
	case HAL_CAP_11D:
		return HAL_OK;

	case HAL_CAP_HT:
		return pCap->halHTSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_GTXTO:
		return pCap->halGTTSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_FAST_CC:
		return pCap->halFastCCSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_TX_CHAINMASK:	/* mask of TX chains supported */
		*result = pCap->halTxChainMask;
		return HAL_OK;
	case HAL_CAP_RX_CHAINMASK:	/* mask of RX chains supported */
		*result = pCap->halRxChainMask;
		return HAL_OK;
	case HAL_CAP_NUM_GPIO_PINS:
		*result = pCap->halNumGpioPins;
		return HAL_OK;
	case HAL_CAP_CST:
		return pCap->halCSTSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_RTS_AGGR_LIMIT:
		*result = pCap->halRtsAggrLimit;
		return HAL_OK;
	case HAL_CAP_4ADDR_AGGR:
		return pCap->hal4AddrAggrSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_EXT_CHAN_DFS:
		return pCap->halExtChanDfsSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_RX_STBC:
		return pCap->halRxStbcSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_TX_STBC:
		return pCap->halTxStbcSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_COMBINED_RADAR_RSSI:
		return pCap->halUseCombinedRadarRssi ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_AUTO_SLEEP:
		return pCap->halAutoSleepSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_MBSSID_AGGR_SUPPORT:
		return pCap->halMbssidAggrSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_SPLIT_4KB_TRANS:	/* hardware handles descriptors straddling 4k page boundary */
		return pCap->hal4kbSplitTransSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_REG_FLAG:
		*result = AH_PRIVATE(ah)->ah_currentRDext;
		return HAL_OK;
	case HAL_CAP_ENHANCED_DMA_SUPPORT:
		return pCap->halEnhancedDmaSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_NUM_TXMAPS:
		*result = pCap->halNumTxMaps;
		return HAL_OK;
	case HAL_CAP_TXDESCLEN:
		*result = pCap->halTxDescLen;
		return HAL_OK;
	case HAL_CAP_TXSTATUSLEN:
		*result = pCap->halTxStatusLen;
		return HAL_OK;
	case HAL_CAP_RXSTATUSLEN:
		*result = pCap->halRxStatusLen;
		return HAL_OK;
	case HAL_CAP_RXFIFODEPTH:
		switch (capability) {
		case HAL_RX_QUEUE_HP:
			*result = pCap->halRxHpFifoDepth;
			return HAL_OK;
		case HAL_RX_QUEUE_LP:
			*result = pCap->halRxLpFifoDepth;
			return HAL_OK;
		default:
			return HAL_ENOTSUPP;
	}
	case HAL_CAP_RXBUFSIZE:
	case HAL_CAP_NUM_MR_RETRIES:
		*result = pCap->halNumMRRetries;
		return HAL_OK;
	case HAL_CAP_BT_COEX:
		return pCap->halBtCoexSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_SPECTRAL_SCAN:
		return pCap->halSpectralScanSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_HT20_SGI:
		return pCap->halHTSGI20Support ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_RXTSTAMP_PREC:	/* rx desc tstamp precision (bits) */
		*result = pCap->halRxTstampPrecision;
		return HAL_OK;
	case HAL_CAP_ANT_DIV_COMB:	/* AR9285/AR9485 LNA diversity */
		return pCap->halAntDivCombSupport ? HAL_OK  : HAL_ENOTSUPP;

	case HAL_CAP_ENHANCED_DFS_SUPPORT:
		return pCap->halEnhancedDfsSupport ? HAL_OK : HAL_ENOTSUPP;

	/* FreeBSD-specific entries for now */
	case HAL_CAP_RXORN_FATAL:	/* HAL_INT_RXORN treated as fatal  */
		return AH_PRIVATE(ah)->ah_rxornIsFatal ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_INTRMASK:		/* mask of supported interrupts */
		*result = pCap->halIntrMask;
		return HAL_OK;
	case HAL_CAP_BSSIDMATCH:	/* hardware has disable bssid match */
		return pCap->halBssidMatchSupport ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_STREAMS:		/* number of 11n spatial streams */
		switch (capability) {
		case 0:			/* TX */
			*result = pCap->halTxStreams;
			return HAL_OK;
		case 1:			/* RX */
			*result = pCap->halRxStreams;
			return HAL_OK;
		default:
			return HAL_ENOTSUPP;
		}
	case HAL_CAP_RXDESC_SELFLINK:	/* hardware supports self-linked final RX descriptors correctly */
		return pCap->halHasRxSelfLinkedTail ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_BB_READ_WAR:		/* Baseband read WAR */
		return pCap->halHasBBReadWar? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_SERIALISE_WAR:		/* PCI register serialisation */
		return pCap->halSerialiseRegWar ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_MFP:			/* Management frame protection setting */
		*result = pCap->halMfpSupport;
		return HAL_OK;
	case HAL_CAP_RX_LNA_MIXING:	/* Hardware uses an RX LNA mixer to map 2 antennas to a 1 stream receiver */
		return pCap->halRxUsingLnaMixing ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_DO_MYBEACON:	/* Hardware supports filtering my-beacons */
		return pCap->halRxDoMyBeacon ? HAL_OK : HAL_ENOTSUPP;
	case HAL_CAP_TXTSTAMP_PREC:	/* tx desc tstamp precision (bits) */
		*result = pCap->halTxTstampPrecision;
		return HAL_OK;
	default:
		return HAL_EINVAL;
	}
}