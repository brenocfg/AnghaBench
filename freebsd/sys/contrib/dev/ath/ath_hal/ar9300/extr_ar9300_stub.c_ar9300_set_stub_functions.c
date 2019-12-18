#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int /*<<< orphan*/  ah_setInterrupts; int /*<<< orphan*/  ah_getInterrupts; int /*<<< orphan*/  ah_getPendingInterrupts; int /*<<< orphan*/  ah_isInterruptPending; int /*<<< orphan*/  ah_getNextTBTT; int /*<<< orphan*/  ah_resetStationBeaconTimers; int /*<<< orphan*/  ah_setStationBeaconTimers; int /*<<< orphan*/  ah_beaconInit; int /*<<< orphan*/  ah_setBeaconTimers; int /*<<< orphan*/  ah_getPowerMode; int /*<<< orphan*/  ah_setPowerMode; int /*<<< orphan*/  ah_setKeyCacheEntryMac; int /*<<< orphan*/  ah_setKeyCacheEntry; int /*<<< orphan*/  ah_isKeyCacheEntryValid; int /*<<< orphan*/  ah_resetKeyCacheEntry; int /*<<< orphan*/  ah_getKeyCacheSize; int /*<<< orphan*/  ah_get11nExtBusy; int /*<<< orphan*/  ah_isFastClockEnabled; int /*<<< orphan*/  ah_procRadarEvent; int /*<<< orphan*/  ah_getDfsThresh; int /*<<< orphan*/  ah_enableDfs; int /*<<< orphan*/  ah_getMibCycleCounts; int /*<<< orphan*/  ah_setQuiet; int /*<<< orphan*/  ah_setCoverageClass; int /*<<< orphan*/  ah_setDecompMask; int /*<<< orphan*/  ah_getCTSTimeout; int /*<<< orphan*/  ah_setCTSTimeout; int /*<<< orphan*/  ah_getAckCTSRate; int /*<<< orphan*/  ah_setAckCTSRate; int /*<<< orphan*/  ah_getAckTimeout; int /*<<< orphan*/  ah_setAckTimeout; int /*<<< orphan*/  ah_getSlotTime; int /*<<< orphan*/  ah_setSlotTime; int /*<<< orphan*/  ah_getSifsTime; int /*<<< orphan*/  ah_setSifsTime; int /*<<< orphan*/  ah_setAntennaSwitch; int /*<<< orphan*/  ah_getAntennaSwitch; int /*<<< orphan*/  ah_setDefAntenna; int /*<<< orphan*/  ah_getDefAntenna; int /*<<< orphan*/  ah_getRfGain; int /*<<< orphan*/  ah_updateMibCounters; int /*<<< orphan*/  ah_detectCardPresent; int /*<<< orphan*/  ah_resetTsf; int /*<<< orphan*/  ah_getTsf64; int /*<<< orphan*/  ah_getTsf32; int /*<<< orphan*/  ah_gpioSetIntr; int /*<<< orphan*/  ah_gpioSet; int /*<<< orphan*/  ah_gpioGet; int /*<<< orphan*/  ah_gpioCfgOutput; int /*<<< orphan*/  ah_gpioCfgInput; int /*<<< orphan*/  ah_writeAssocid; int /*<<< orphan*/  ah_setLedState; int /*<<< orphan*/  ah_setRegulatoryDomain; int /*<<< orphan*/  ah_setBssIdMask; int /*<<< orphan*/  ah_getBssIdMask; int /*<<< orphan*/  ah_setMacAddress; int /*<<< orphan*/  ah_getMacAddress; int /*<<< orphan*/  ah_getDiagState; int /*<<< orphan*/  ah_setCapability; int /*<<< orphan*/  ah_getCapability; int /*<<< orphan*/  ah_procMibEvent; int /*<<< orphan*/  ah_aniPoll; int /*<<< orphan*/  ah_rxMonitor; int /*<<< orphan*/  ah_procRxDesc; int /*<<< orphan*/  ah_setupRxDesc; int /*<<< orphan*/  ah_setRxFilter; int /*<<< orphan*/  ah_getRxFilter; int /*<<< orphan*/  ah_clrMulticastFilterIndex; int /*<<< orphan*/  ah_setMulticastFilterIndex; int /*<<< orphan*/  ah_setMulticastFilter; int /*<<< orphan*/  ah_stopPcuReceive; int /*<<< orphan*/  ah_startPcuReceive; int /*<<< orphan*/  ah_stopDmaReceive; int /*<<< orphan*/  ah_enableReceive; int /*<<< orphan*/  ah_setRxDP; int /*<<< orphan*/  ah_getRxDP; int /*<<< orphan*/  ah_getTxCompletionRates; int /*<<< orphan*/  ah_reqTxIntrDesc; int /*<<< orphan*/  ah_getTxIntrQueue; int /*<<< orphan*/  ah_procTxDesc; int /*<<< orphan*/  ah_fillTxDesc; int /*<<< orphan*/  ah_setupXTxDesc; int /*<<< orphan*/  ah_setupTxDesc; int /*<<< orphan*/  ah_stopTxDma; int /*<<< orphan*/  ah_startTxDma; int /*<<< orphan*/  ah_numTxPending; int /*<<< orphan*/  ah_setTxDP; int /*<<< orphan*/  ah_getTxDP; int /*<<< orphan*/  ah_resetTxQueue; int /*<<< orphan*/  ah_releaseTxQueue; int /*<<< orphan*/  ah_getTxQueueProps; int /*<<< orphan*/  ah_setTxQueueProps; int /*<<< orphan*/  ah_setupTxQueue; int /*<<< orphan*/  ah_updateTxTrigLevel; int /*<<< orphan*/  ah_getChanNoise; int /*<<< orphan*/  ah_setTxPowerLimit; int /*<<< orphan*/  ah_resetCalValid; int /*<<< orphan*/  ah_perCalibrationN; int /*<<< orphan*/  ah_perCalibration; int /*<<< orphan*/  ah_setPCUConfig; int /*<<< orphan*/  ah_disablePCIE; int /*<<< orphan*/  ah_configPCIE; int /*<<< orphan*/  ah_disable; int /*<<< orphan*/  ah_phyDisable; int /*<<< orphan*/  ah_reset; int /*<<< orphan*/  ah_getRateTable; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_getChipPowerLimits; int /*<<< orphan*/  ah_eepromWrite; int /*<<< orphan*/  ah_eepromRead; int /*<<< orphan*/  ah_getWirelessModes; int /*<<< orphan*/  ah_getChannelEdges; } ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_Stub_AniPoll ; 
 int /*<<< orphan*/  ar9300_Stub_BeaconInit ; 
 int /*<<< orphan*/  ar9300_Stub_ClrMulticastFilterIndex ; 
 int /*<<< orphan*/  ar9300_Stub_ConfigPCIE ; 
 int /*<<< orphan*/  ar9300_Stub_DetectCardPresent ; 
 int /*<<< orphan*/  ar9300_Stub_Disable ; 
 int /*<<< orphan*/  ar9300_Stub_DisablePCIE ; 
 int /*<<< orphan*/  ar9300_Stub_EepromRead ; 
 int /*<<< orphan*/  ar9300_Stub_EepromWrite ; 
 int /*<<< orphan*/  ar9300_Stub_EnableDfs ; 
 int /*<<< orphan*/  ar9300_Stub_EnableReceive ; 
 int /*<<< orphan*/  ar9300_Stub_FillTxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_Get11nExtBusy ; 
 int /*<<< orphan*/  ar9300_Stub_GetAckCTSRate ; 
 int /*<<< orphan*/  ar9300_Stub_GetAckTimeout ; 
 int /*<<< orphan*/  ar9300_Stub_GetAntennaSwitch ; 
 int /*<<< orphan*/  ar9300_Stub_GetBssIdMask ; 
 int /*<<< orphan*/  ar9300_Stub_GetCTSTimeout ; 
 int /*<<< orphan*/  ar9300_Stub_GetCapability ; 
 int /*<<< orphan*/  ar9300_Stub_GetChannelEdges ; 
 int /*<<< orphan*/  ar9300_Stub_GetChipPowerLimits ; 
 int /*<<< orphan*/  ar9300_Stub_GetDefAntenna ; 
 int /*<<< orphan*/  ar9300_Stub_GetDfsThresh ; 
 int /*<<< orphan*/  ar9300_Stub_GetDiagState ; 
 int /*<<< orphan*/  ar9300_Stub_GetInterrupts ; 
 int /*<<< orphan*/  ar9300_Stub_GetKeyCacheSize ; 
 int /*<<< orphan*/  ar9300_Stub_GetMacAddress ; 
 int /*<<< orphan*/  ar9300_Stub_GetMibCycleCounts ; 
 int /*<<< orphan*/  ar9300_Stub_GetNextTBTT ; 
 int /*<<< orphan*/  ar9300_Stub_GetPendingInterrupts ; 
 int /*<<< orphan*/  ar9300_Stub_GetPowerMode ; 
 int /*<<< orphan*/  ar9300_Stub_GetRateTable ; 
 int /*<<< orphan*/  ar9300_Stub_GetRfgain ; 
 int /*<<< orphan*/  ar9300_Stub_GetRxDP ; 
 int /*<<< orphan*/  ar9300_Stub_GetRxFilter ; 
 int /*<<< orphan*/  ar9300_Stub_GetSifsTime ; 
 int /*<<< orphan*/  ar9300_Stub_GetSlotTime ; 
 int /*<<< orphan*/  ar9300_Stub_GetTsf32 ; 
 int /*<<< orphan*/  ar9300_Stub_GetTsf64 ; 
 int /*<<< orphan*/  ar9300_Stub_GetTxCompletionRates ; 
 int /*<<< orphan*/  ar9300_Stub_GetTxDP ; 
 int /*<<< orphan*/  ar9300_Stub_GetTxIntrQueue ; 
 int /*<<< orphan*/  ar9300_Stub_GetTxQueueProps ; 
 int /*<<< orphan*/  ar9300_Stub_GetWirelessModes ; 
 int /*<<< orphan*/  ar9300_Stub_GpioCfgInput ; 
 int /*<<< orphan*/  ar9300_Stub_GpioCfgOutput ; 
 int /*<<< orphan*/  ar9300_Stub_GpioGet ; 
 int /*<<< orphan*/  ar9300_Stub_GpioSet ; 
 int /*<<< orphan*/  ar9300_Stub_GpioSetIntr ; 
 int /*<<< orphan*/  ar9300_Stub_IntrReqTxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_IsFastClockEnabled ; 
 int /*<<< orphan*/  ar9300_Stub_IsInterruptPending ; 
 int /*<<< orphan*/  ar9300_Stub_IsKeyCacheEntryValid ; 
 int /*<<< orphan*/  ar9300_Stub_NumTxPending ; 
 int /*<<< orphan*/  ar9300_Stub_PerCalibration ; 
 int /*<<< orphan*/  ar9300_Stub_PerCalibrationN ; 
 int /*<<< orphan*/  ar9300_Stub_PhyDisable ; 
 int /*<<< orphan*/  ar9300_Stub_ProcRxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_ProcTxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_ProcessMibIntr ; 
 int /*<<< orphan*/  ar9300_Stub_ProcessRadarEvent ; 
 int /*<<< orphan*/  ar9300_Stub_ReleaseTxQueue ; 
 int /*<<< orphan*/  ar9300_Stub_Reset ; 
 int /*<<< orphan*/  ar9300_Stub_ResetCalValid ; 
 int /*<<< orphan*/  ar9300_Stub_ResetKeyCacheEntry ; 
 int /*<<< orphan*/  ar9300_Stub_ResetStaBeaconTimers ; 
 int /*<<< orphan*/  ar9300_Stub_ResetTsf ; 
 int /*<<< orphan*/  ar9300_Stub_ResetTxQueue ; 
 int /*<<< orphan*/  ar9300_Stub_RxMonitor ; 
 int /*<<< orphan*/  ar9300_Stub_SetAckCTSRate ; 
 int /*<<< orphan*/  ar9300_Stub_SetAckTimeout ; 
 int /*<<< orphan*/  ar9300_Stub_SetAntennaSwitch ; 
 int /*<<< orphan*/  ar9300_Stub_SetBeaconTimers ; 
 int /*<<< orphan*/  ar9300_Stub_SetBssIdMask ; 
 int /*<<< orphan*/  ar9300_Stub_SetCTSTimeout ; 
 int /*<<< orphan*/  ar9300_Stub_SetCapability ; 
 int /*<<< orphan*/  ar9300_Stub_SetCoverageClass ; 
 int /*<<< orphan*/  ar9300_Stub_SetDecompMask ; 
 int /*<<< orphan*/  ar9300_Stub_SetDefAntenna ; 
 int /*<<< orphan*/  ar9300_Stub_SetInterrupts ; 
 int /*<<< orphan*/  ar9300_Stub_SetKeyCacheEntry ; 
 int /*<<< orphan*/  ar9300_Stub_SetKeyCacheEntryMac ; 
 int /*<<< orphan*/  ar9300_Stub_SetLedState ; 
 int /*<<< orphan*/  ar9300_Stub_SetMacAddress ; 
 int /*<<< orphan*/  ar9300_Stub_SetMulticastFilter ; 
 int /*<<< orphan*/  ar9300_Stub_SetMulticastFilterIndex ; 
 int /*<<< orphan*/  ar9300_Stub_SetPCUConfig ; 
 int /*<<< orphan*/  ar9300_Stub_SetPowerMode ; 
 int /*<<< orphan*/  ar9300_Stub_SetQuiet ; 
 int /*<<< orphan*/  ar9300_Stub_SetRegulatoryDomain ; 
 int /*<<< orphan*/  ar9300_Stub_SetRxDP ; 
 int /*<<< orphan*/  ar9300_Stub_SetRxFilter ; 
 int /*<<< orphan*/  ar9300_Stub_SetSifsTime ; 
 int /*<<< orphan*/  ar9300_Stub_SetSlotTime ; 
 int /*<<< orphan*/  ar9300_Stub_SetStaBeaconTimers ; 
 int /*<<< orphan*/  ar9300_Stub_SetTxDP ; 
 int /*<<< orphan*/  ar9300_Stub_SetTxPowerLimit ; 
 int /*<<< orphan*/  ar9300_Stub_SetTxQueueProps ; 
 int /*<<< orphan*/  ar9300_Stub_SetupRxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_SetupTxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_SetupTxQueue ; 
 int /*<<< orphan*/  ar9300_Stub_SetupXTxDesc ; 
 int /*<<< orphan*/  ar9300_Stub_StartPcuReceive ; 
 int /*<<< orphan*/  ar9300_Stub_StartTxDma ; 
 int /*<<< orphan*/  ar9300_Stub_StopDmaReceive ; 
 int /*<<< orphan*/  ar9300_Stub_StopPcuReceive ; 
 int /*<<< orphan*/  ar9300_Stub_StopTxDma ; 
 int /*<<< orphan*/  ar9300_Stub_UpdateMibCounters ; 
 int /*<<< orphan*/  ar9300_Stub_UpdateTxTrigLevel ; 
 int /*<<< orphan*/  ar9300_Stub_WriteAssocid ; 
 int /*<<< orphan*/  ath_hal_getChanNoise ; 

void
ar9300_set_stub_functions(struct ath_hal *ah)
{

//	ath_hal_printf(ah, "%s: setting stub functions\n", __func__);

	ah->ah_getRateTable		= ar9300_Stub_GetRateTable;
//	ah->ah_detach			= ar9300_Stub_detach;

	/* Reset Functions */
	ah->ah_reset			= ar9300_Stub_Reset;
	ah->ah_phyDisable		= ar9300_Stub_PhyDisable;
	ah->ah_disable			= ar9300_Stub_Disable;
	ah->ah_configPCIE		= ar9300_Stub_ConfigPCIE;
	ah->ah_disablePCIE		= ar9300_Stub_DisablePCIE;
	ah->ah_setPCUConfig		= ar9300_Stub_SetPCUConfig;
	ah->ah_perCalibration		= ar9300_Stub_PerCalibration;
	ah->ah_perCalibrationN		= ar9300_Stub_PerCalibrationN;
	ah->ah_resetCalValid		= ar9300_Stub_ResetCalValid;
	ah->ah_setTxPowerLimit		= ar9300_Stub_SetTxPowerLimit;
	ah->ah_getChanNoise		= ath_hal_getChanNoise;

	/* Transmit functions */
	ah->ah_updateTxTrigLevel	= ar9300_Stub_UpdateTxTrigLevel;
	ah->ah_setupTxQueue		= ar9300_Stub_SetupTxQueue;
	ah->ah_setTxQueueProps		= ar9300_Stub_SetTxQueueProps;
	ah->ah_getTxQueueProps		= ar9300_Stub_GetTxQueueProps;
	ah->ah_releaseTxQueue		= ar9300_Stub_ReleaseTxQueue;
	ah->ah_resetTxQueue		= ar9300_Stub_ResetTxQueue;
	ah->ah_getTxDP			= ar9300_Stub_GetTxDP;
	ah->ah_setTxDP			= ar9300_Stub_SetTxDP;
	ah->ah_numTxPending		= ar9300_Stub_NumTxPending;
	ah->ah_startTxDma		= ar9300_Stub_StartTxDma;
	ah->ah_stopTxDma		= ar9300_Stub_StopTxDma;
	ah->ah_setupTxDesc		= ar9300_Stub_SetupTxDesc;
	ah->ah_setupXTxDesc		= ar9300_Stub_SetupXTxDesc;
	ah->ah_fillTxDesc		= ar9300_Stub_FillTxDesc;
	ah->ah_procTxDesc		= ar9300_Stub_ProcTxDesc;
	ah->ah_getTxIntrQueue		= ar9300_Stub_GetTxIntrQueue;
	ah->ah_reqTxIntrDesc 		= ar9300_Stub_IntrReqTxDesc;
	ah->ah_getTxCompletionRates	= ar9300_Stub_GetTxCompletionRates;

	/* RX Functions */
	ah->ah_getRxDP			= ar9300_Stub_GetRxDP;
	ah->ah_setRxDP			= ar9300_Stub_SetRxDP;
	ah->ah_enableReceive		= ar9300_Stub_EnableReceive;
	ah->ah_stopDmaReceive		= ar9300_Stub_StopDmaReceive;
	ah->ah_startPcuReceive		= ar9300_Stub_StartPcuReceive;
	ah->ah_stopPcuReceive		= ar9300_Stub_StopPcuReceive;
	ah->ah_setMulticastFilter	= ar9300_Stub_SetMulticastFilter;
	ah->ah_setMulticastFilterIndex	= ar9300_Stub_SetMulticastFilterIndex;
	ah->ah_clrMulticastFilterIndex	= ar9300_Stub_ClrMulticastFilterIndex;
	ah->ah_getRxFilter		= ar9300_Stub_GetRxFilter;
	ah->ah_setRxFilter		= ar9300_Stub_SetRxFilter;
	ah->ah_setupRxDesc		= ar9300_Stub_SetupRxDesc;
	ah->ah_procRxDesc		= ar9300_Stub_ProcRxDesc;
	ah->ah_rxMonitor		= ar9300_Stub_RxMonitor;
	ah->ah_aniPoll			= ar9300_Stub_AniPoll;
	ah->ah_procMibEvent		= ar9300_Stub_ProcessMibIntr;

	/* Misc Functions */
	ah->ah_getCapability		= ar9300_Stub_GetCapability;
	ah->ah_setCapability		= ar9300_Stub_SetCapability;
	ah->ah_getDiagState		= ar9300_Stub_GetDiagState;
	ah->ah_getMacAddress		= ar9300_Stub_GetMacAddress;
	ah->ah_setMacAddress		= ar9300_Stub_SetMacAddress;
	ah->ah_getBssIdMask		= ar9300_Stub_GetBssIdMask;
	ah->ah_setBssIdMask		= ar9300_Stub_SetBssIdMask;
	ah->ah_setRegulatoryDomain	= ar9300_Stub_SetRegulatoryDomain;
	ah->ah_setLedState		= ar9300_Stub_SetLedState;
	ah->ah_writeAssocid		= ar9300_Stub_WriteAssocid;
	ah->ah_gpioCfgInput		= ar9300_Stub_GpioCfgInput;
	ah->ah_gpioCfgOutput		= ar9300_Stub_GpioCfgOutput;
	ah->ah_gpioGet			= ar9300_Stub_GpioGet;
	ah->ah_gpioSet			= ar9300_Stub_GpioSet;
	ah->ah_gpioSetIntr		= ar9300_Stub_GpioSetIntr;
	ah->ah_getTsf32			= ar9300_Stub_GetTsf32;
	ah->ah_getTsf64			= ar9300_Stub_GetTsf64;
	ah->ah_resetTsf			= ar9300_Stub_ResetTsf;
	ah->ah_detectCardPresent	= ar9300_Stub_DetectCardPresent;
	ah->ah_updateMibCounters	= ar9300_Stub_UpdateMibCounters;
	ah->ah_getRfGain		= ar9300_Stub_GetRfgain;
	ah->ah_getDefAntenna		= ar9300_Stub_GetDefAntenna;
	ah->ah_setDefAntenna		= ar9300_Stub_SetDefAntenna;
	ah->ah_getAntennaSwitch		= ar9300_Stub_GetAntennaSwitch;
	ah->ah_setAntennaSwitch		= ar9300_Stub_SetAntennaSwitch;
	ah->ah_setSifsTime		= ar9300_Stub_SetSifsTime;
	ah->ah_getSifsTime		= ar9300_Stub_GetSifsTime;
	ah->ah_setSlotTime		= ar9300_Stub_SetSlotTime;
	ah->ah_getSlotTime		= ar9300_Stub_GetSlotTime;
	ah->ah_setAckTimeout		= ar9300_Stub_SetAckTimeout;
	ah->ah_getAckTimeout		= ar9300_Stub_GetAckTimeout;
	ah->ah_setAckCTSRate		= ar9300_Stub_SetAckCTSRate;
	ah->ah_getAckCTSRate		= ar9300_Stub_GetAckCTSRate;
	ah->ah_setCTSTimeout		= ar9300_Stub_SetCTSTimeout;
	ah->ah_getCTSTimeout		= ar9300_Stub_GetCTSTimeout;
	ah->ah_setDecompMask		= ar9300_Stub_SetDecompMask;
	ah->ah_setCoverageClass		= ar9300_Stub_SetCoverageClass;
	ah->ah_setQuiet			= ar9300_Stub_SetQuiet;
	ah->ah_getMibCycleCounts	= ar9300_Stub_GetMibCycleCounts;

	/* DFS Functions */
	ah->ah_enableDfs		= ar9300_Stub_EnableDfs;
	ah->ah_getDfsThresh		= ar9300_Stub_GetDfsThresh;
	ah->ah_procRadarEvent		= ar9300_Stub_ProcessRadarEvent;
	ah->ah_isFastClockEnabled	= ar9300_Stub_IsFastClockEnabled;
	ah->ah_get11nExtBusy		= ar9300_Stub_Get11nExtBusy;

	/* Key Cache Functions */
	ah->ah_getKeyCacheSize		= ar9300_Stub_GetKeyCacheSize;
	ah->ah_resetKeyCacheEntry	= ar9300_Stub_ResetKeyCacheEntry;
	ah->ah_isKeyCacheEntryValid	= ar9300_Stub_IsKeyCacheEntryValid;
	ah->ah_setKeyCacheEntry		= ar9300_Stub_SetKeyCacheEntry;
	ah->ah_setKeyCacheEntryMac	= ar9300_Stub_SetKeyCacheEntryMac;

	/* Power Management Functions */
	ah->ah_setPowerMode		= ar9300_Stub_SetPowerMode;
	ah->ah_getPowerMode		= ar9300_Stub_GetPowerMode;

	/* Beacon Functions */
	ah->ah_setBeaconTimers		= ar9300_Stub_SetBeaconTimers;
	ah->ah_beaconInit		= ar9300_Stub_BeaconInit;
	ah->ah_setStationBeaconTimers	= ar9300_Stub_SetStaBeaconTimers;
	ah->ah_resetStationBeaconTimers	= ar9300_Stub_ResetStaBeaconTimers;
	ah->ah_getNextTBTT		= ar9300_Stub_GetNextTBTT;

	/* Interrupt Functions */
	ah->ah_isInterruptPending	= ar9300_Stub_IsInterruptPending;
	ah->ah_getPendingInterrupts	= ar9300_Stub_GetPendingInterrupts;
	ah->ah_getInterrupts		= ar9300_Stub_GetInterrupts;
	ah->ah_setInterrupts		= ar9300_Stub_SetInterrupts;

	AH_PRIVATE(ah)->ah_getChannelEdges		= ar9300_Stub_GetChannelEdges;
	AH_PRIVATE(ah)->ah_getWirelessModes		= ar9300_Stub_GetWirelessModes;
	AH_PRIVATE(ah)->ah_eepromRead		= ar9300_Stub_EepromRead;
#ifdef AH_SUPPORT_WRITE_EEPROM
	AH_PRIVATE(ah)->ah_eepromWrite		= ar9300_Stub_EepromWrite;
#endif
	AH_PRIVATE(ah)->ah_getChipPowerLimits	= ar9300_Stub_GetChipPowerLimits;
}