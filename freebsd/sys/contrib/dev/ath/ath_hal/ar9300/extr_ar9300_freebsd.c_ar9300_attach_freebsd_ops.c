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
struct ath_hal {int /*<<< orphan*/  ah_divLnaConfSet; int /*<<< orphan*/  ah_divLnaConfGet; int /*<<< orphan*/  ah_btMciDetach; int /*<<< orphan*/  ah_btMciState; int /*<<< orphan*/  ah_btMciGetInterrupt; int /*<<< orphan*/  ah_btMciSendMessage; int /*<<< orphan*/  ah_btMciSetup; int /*<<< orphan*/  ah_btCoexEnable; int /*<<< orphan*/  ah_btCoexDisable; int /*<<< orphan*/  ah_btCoexSetWeights; int /*<<< orphan*/  ah_btCoexSetParameter; int /*<<< orphan*/  ah_btCoexSetBmissThresh; int /*<<< orphan*/  ah_btCoexSetQcuThresh; int /*<<< orphan*/  ah_btCoexSetConfig; int /*<<< orphan*/  ah_btCoexSetInfo; int /*<<< orphan*/  ah_setChainMasks; int /*<<< orphan*/  ah_set11nMac2040; int /*<<< orphan*/  ah_set11nBurstDuration; int /*<<< orphan*/  ah_clr11nAggr; int /*<<< orphan*/  ah_set11nAggrLast; int /*<<< orphan*/  ah_set11nAggrMiddle; int /*<<< orphan*/  ah_set11nAggrFirst; int /*<<< orphan*/  ah_set11nTxDesc; int /*<<< orphan*/  ah_set11nRateScenario; int /*<<< orphan*/  ah_setupLastTxDesc; int /*<<< orphan*/  ah_setupFirstTxDesc; int /*<<< orphan*/  ah_chainTxDesc; int /*<<< orphan*/  ah_setInterrupts; int /*<<< orphan*/  ah_getInterrupts; int /*<<< orphan*/  ah_getPendingInterrupts; int /*<<< orphan*/  ah_isInterruptPending; int /*<<< orphan*/  ah_getNextTBTT; int /*<<< orphan*/  ah_setStationBeaconTimers; int /*<<< orphan*/  ah_setBeaconTimers; int /*<<< orphan*/  ah_beaconInit; int /*<<< orphan*/  ah_getPowerMode; int /*<<< orphan*/  ah_setPowerMode; int /*<<< orphan*/  ah_setKeyCacheEntryMac; int /*<<< orphan*/  ah_setKeyCacheEntry; int /*<<< orphan*/  ah_isKeyCacheEntryValid; int /*<<< orphan*/  ah_resetKeyCacheEntry; int /*<<< orphan*/  ah_getKeyCacheSize; int /*<<< orphan*/  ah_spectralIsActive; int /*<<< orphan*/  ah_spectralIsEnabled; int /*<<< orphan*/  ah_spectralStop; int /*<<< orphan*/  ah_spectralStart; int /*<<< orphan*/  ah_spectralGetConfig; int /*<<< orphan*/  ah_spectralConfigure; int /*<<< orphan*/  ah_setDfsCacTxQuiet; int /*<<< orphan*/  ah_get11nExtBusy; int /*<<< orphan*/  ah_isFastClockEnabled; int /*<<< orphan*/  ah_procRadarEvent; int /*<<< orphan*/  ah_getDfsDefaultThresh; int /*<<< orphan*/  ah_getDfsThresh; int /*<<< orphan*/  ah_enableDfs; int /*<<< orphan*/  ah_getMibCycleCounts; int /*<<< orphan*/  ah_setQuiet; int /*<<< orphan*/  ah_getCTSTimeout; int /*<<< orphan*/  ah_setAckTimeout; int /*<<< orphan*/  ah_getAckTimeout; int /*<<< orphan*/  ah_getSlotTime; int /*<<< orphan*/  ah_setSlotTime; int /*<<< orphan*/  ah_setAntennaSwitch; int /*<<< orphan*/  ah_getAntennaSwitch; int /*<<< orphan*/  ah_setDefAntenna; int /*<<< orphan*/  ah_getDefAntenna; int /*<<< orphan*/  ah_getRfGain; int /*<<< orphan*/  ah_detectCardPresent; int /*<<< orphan*/  ah_setTsf64; int /*<<< orphan*/  ah_resetTsf; int /*<<< orphan*/  ah_getTsf64; int /*<<< orphan*/  ah_getTsf32; int /*<<< orphan*/  ah_gpioSetIntr; int /*<<< orphan*/  ah_gpioSet; int /*<<< orphan*/  ah_gpioGet; int /*<<< orphan*/  ah_gpioCfgOutput; int /*<<< orphan*/  ah_gpioCfgInput; int /*<<< orphan*/  ah_writeAssocid; int /*<<< orphan*/  ah_setLedState; int /*<<< orphan*/  ah_setRegulatoryDomain; int /*<<< orphan*/  ah_setBssIdMask; int /*<<< orphan*/  ah_getBssIdMask; int /*<<< orphan*/  ah_setMacAddress; int /*<<< orphan*/  ah_getMacAddress; int /*<<< orphan*/  ah_getDiagState; int /*<<< orphan*/  ah_setCapability; int /*<<< orphan*/  ah_getCapability; int /*<<< orphan*/  ah_procMibEvent; int /*<<< orphan*/  ah_aniPoll; int /*<<< orphan*/  ah_rxMonitor; int /*<<< orphan*/  ah_procRxDesc; int /*<<< orphan*/  ah_setRxFilter; int /*<<< orphan*/  ah_getRxFilter; int /*<<< orphan*/  ah_clrMulticastFilterIndex; int /*<<< orphan*/  ah_setMulticastFilterIndex; int /*<<< orphan*/  ah_setMulticastFilter; int /*<<< orphan*/  ah_stopPcuReceive; int /*<<< orphan*/  ah_startPcuReceive; int /*<<< orphan*/  ah_stopDmaReceive; int /*<<< orphan*/  ah_enableReceive; int /*<<< orphan*/  ah_setRxDP; int /*<<< orphan*/  ah_getRxDP; int /*<<< orphan*/  ah_updateTxTrigLevel; int /*<<< orphan*/  ah_getTxRawTxDesc; int /*<<< orphan*/  ah_setupTxStatusRing; int /*<<< orphan*/  ah_getTxDescLinkPtr; int /*<<< orphan*/  ah_getTxDescLink; int /*<<< orphan*/  ah_setTxDescLink; int /*<<< orphan*/  ah_getTxCompletionRates; int /*<<< orphan*/  ah_getTxIntrQueue; int /*<<< orphan*/  ah_procTxDesc; int /*<<< orphan*/  ah_fillTxDesc; int /*<<< orphan*/  ah_setupXTxDesc; int /*<<< orphan*/  ah_setupTxDesc; int /*<<< orphan*/  ah_stopTxDma; int /*<<< orphan*/  ah_startTxDma; int /*<<< orphan*/  ah_numTxPending; int /*<<< orphan*/  ah_setTxDP; int /*<<< orphan*/  ah_getTxDP; int /*<<< orphan*/  ah_resetTxQueue; int /*<<< orphan*/  ah_releaseTxQueue; int /*<<< orphan*/  ah_getTxQueueProps; int /*<<< orphan*/  ah_setTxQueueProps; int /*<<< orphan*/  ah_setupTxQueue; int /*<<< orphan*/  ah_getChanNoise; int /*<<< orphan*/  ah_setTxPowerLimit; int /*<<< orphan*/  ah_resetCalValid; int /*<<< orphan*/  ah_perCalibrationN; int /*<<< orphan*/  ah_setPCUConfig; int /*<<< orphan*/  ah_configPCIE; int /*<<< orphan*/  ah_disable; int /*<<< orphan*/  ah_phyDisable; int /*<<< orphan*/  ah_reset; int /*<<< orphan*/  ah_getRateTable; int /*<<< orphan*/  ah_detach; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_eepromGet; void* ah_eepromRead; int /*<<< orphan*/  ah_getChannelEdges; int /*<<< orphan*/  ah_getWirelessModes; } ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_APHRODITE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300ClrMulticastFilterIndex ; 
 int /*<<< orphan*/  ar9300GetSlotTime ; 
 int /*<<< orphan*/  ar9300SetChainMasks ; 
 int /*<<< orphan*/  ar9300SetMulticastFilterIndex ; 
 int /*<<< orphan*/  ar9300_ani_poll_freebsd ; 
 int /*<<< orphan*/  ar9300_ani_rxmonitor_freebsd ; 
 int /*<<< orphan*/  ar9300_ant_div_comb_get_config ; 
 int /*<<< orphan*/  ar9300_ant_div_comb_set_config ; 
 int /*<<< orphan*/  ar9300_beacon_set_beacon_timers ; 
 int /*<<< orphan*/  ar9300_bt_coex_config ; 
 int /*<<< orphan*/  ar9300_bt_coex_disable ; 
 int /*<<< orphan*/  ar9300_bt_coex_enable ; 
 int /*<<< orphan*/  ar9300_bt_coex_set_parameter ; 
 int /*<<< orphan*/  ar9300_bt_coex_set_qcu_thresh ; 
 int /*<<< orphan*/  ar9300_bt_coex_set_weights ; 
 int /*<<< orphan*/  ar9300_bt_coex_setup_bmiss_thresh ; 
 int /*<<< orphan*/  ar9300_cac_tx_quiet ; 
 int /*<<< orphan*/  ar9300_clr_11n_aggr ; 
 int /*<<< orphan*/  ar9300_config_pcie_freebsd ; 
 int /*<<< orphan*/  ar9300_configure_spectral_scan ; 
 int /*<<< orphan*/  ar9300_detach ; 
 int /*<<< orphan*/  ar9300_detect_card_present ; 
 int /*<<< orphan*/  ar9300_disable ; 
 int /*<<< orphan*/  ar9300_eeprom_get_freebsd ; 
 void* ar9300_eeprom_read_word ; 
 int /*<<< orphan*/  ar9300_enable_dfs ; 
 int /*<<< orphan*/  ar9300_enable_receive ; 
 int /*<<< orphan*/  ar9300_freebsd_beacon_init ; 
 int /*<<< orphan*/  ar9300_freebsd_chain_tx_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_fill_tx_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_get_antenna_switch ; 
 int /*<<< orphan*/  ar9300_freebsd_get_cts_timeout ; 
 int /*<<< orphan*/  ar9300_freebsd_get_desc_link ; 
 int /*<<< orphan*/  ar9300_freebsd_get_mib_cycle_counts ; 
 int /*<<< orphan*/  ar9300_freebsd_get_tx_completion_rates ; 
 int /*<<< orphan*/  ar9300_freebsd_proc_radar_event ; 
 int /*<<< orphan*/  ar9300_freebsd_proc_tx_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_set_11n_rate_scenario ; 
 int /*<<< orphan*/  ar9300_freebsd_set_antenna_switch ; 
 int /*<<< orphan*/  ar9300_freebsd_set_tsf64 ; 
 int /*<<< orphan*/  ar9300_freebsd_set_tx_power_limit ; 
 int /*<<< orphan*/  ar9300_freebsd_setup_11n_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_setup_first_tx_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_setup_last_tx_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_setup_tx_desc ; 
 int /*<<< orphan*/  ar9300_freebsd_setup_x_tx_desc ; 
 int /*<<< orphan*/  ar9300_get_11n_ext_busy ; 
 int /*<<< orphan*/  ar9300_get_ack_timeout ; 
 int /*<<< orphan*/  ar9300_get_bss_id_mask ; 
 int /*<<< orphan*/  ar9300_get_capability ; 
 int /*<<< orphan*/  ar9300_get_channel_edges ; 
 int /*<<< orphan*/  ar9300_get_def_antenna ; 
 int /*<<< orphan*/  ar9300_get_default_dfs_thresh ; 
 int /*<<< orphan*/  ar9300_get_desc_link_ptr ; 
 int /*<<< orphan*/  ar9300_get_dfs_thresh ; 
 int /*<<< orphan*/  ar9300_get_diag_state ; 
 int /*<<< orphan*/  ar9300_get_interrupts ; 
 int /*<<< orphan*/  ar9300_get_key_cache_size ; 
 int /*<<< orphan*/  ar9300_get_mac_address ; 
 int /*<<< orphan*/  ar9300_get_next_tbtt ; 
 int /*<<< orphan*/  ar9300_get_pending_interrupts_freebsd ; 
 int /*<<< orphan*/  ar9300_get_power_mode ; 
 int /*<<< orphan*/  ar9300_get_rate_table ; 
 int /*<<< orphan*/  ar9300_get_raw_tx_desc ; 
 int /*<<< orphan*/  ar9300_get_rfgain ; 
 int /*<<< orphan*/  ar9300_get_rx_dp ; 
 int /*<<< orphan*/  ar9300_get_rx_filter ; 
 int /*<<< orphan*/  ar9300_get_spectral_params ; 
 int /*<<< orphan*/  ar9300_get_tsf32 ; 
 int /*<<< orphan*/  ar9300_get_tsf64 ; 
 int /*<<< orphan*/  ar9300_get_tx_dp ; 
 int /*<<< orphan*/  ar9300_get_tx_intr_queue ; 
 int /*<<< orphan*/  ar9300_get_tx_queue_props ; 
 int /*<<< orphan*/  ar9300_get_wireless_modes ; 
 int /*<<< orphan*/  ar9300_gpio_cfg_input ; 
 int /*<<< orphan*/  ar9300_gpio_cfg_output ; 
 int /*<<< orphan*/  ar9300_gpio_get ; 
 int /*<<< orphan*/  ar9300_gpio_set ; 
 int /*<<< orphan*/  ar9300_gpio_set_intr ; 
 int /*<<< orphan*/  ar9300_is_fast_clock_enabled ; 
 int /*<<< orphan*/  ar9300_is_interrupt_pending ; 
 int /*<<< orphan*/  ar9300_is_key_cache_entry_valid ; 
 int /*<<< orphan*/  ar9300_is_spectral_active ; 
 int /*<<< orphan*/  ar9300_is_spectral_enabled ; 
 int /*<<< orphan*/  ar9300_mci_bt_coex_disable ; 
 int /*<<< orphan*/  ar9300_mci_bt_coex_enable ; 
 int /*<<< orphan*/  ar9300_mci_bt_coex_set_weights ; 
 int /*<<< orphan*/  ar9300_mci_detach ; 
 int /*<<< orphan*/  ar9300_mci_get_interrupt ; 
 int /*<<< orphan*/  ar9300_mci_send_message ; 
 int /*<<< orphan*/  ar9300_mci_setup ; 
 int /*<<< orphan*/  ar9300_mci_state ; 
 int /*<<< orphan*/  ar9300_num_tx_pending ; 
 int /*<<< orphan*/  ar9300_per_calibration_freebsd ; 
 int /*<<< orphan*/  ar9300_phy_disable ; 
 int /*<<< orphan*/  ar9300_proc_rx_desc_freebsd ; 
 int /*<<< orphan*/  ar9300_process_mib_intr ; 
 int /*<<< orphan*/  ar9300_release_tx_queue ; 
 int /*<<< orphan*/  ar9300_reset_cal_valid_freebsd ; 
 int /*<<< orphan*/  ar9300_reset_freebsd ; 
 int /*<<< orphan*/  ar9300_reset_key_cache_entry ; 
 int /*<<< orphan*/  ar9300_reset_tsf ; 
 int /*<<< orphan*/  ar9300_reset_tx_queue ; 
 int /*<<< orphan*/  ar9300_set_11n_aggr_first ; 
 int /*<<< orphan*/  ar9300_set_11n_aggr_last ; 
 int /*<<< orphan*/  ar9300_set_11n_aggr_middle ; 
 int /*<<< orphan*/  ar9300_set_11n_burst_duration ; 
 int /*<<< orphan*/  ar9300_set_11n_mac2040 ; 
 int /*<<< orphan*/  ar9300_set_ack_timeout ; 
 int /*<<< orphan*/  ar9300_set_bss_id_mask ; 
 int /*<<< orphan*/  ar9300_set_bt_coex_info ; 
 int /*<<< orphan*/  ar9300_set_capability ; 
 int /*<<< orphan*/  ar9300_set_def_antenna ; 
 int /*<<< orphan*/  ar9300_set_desc_link ; 
 int /*<<< orphan*/  ar9300_set_interrupts_freebsd ; 
 int /*<<< orphan*/  ar9300_set_key_cache_entry ; 
 int /*<<< orphan*/  ar9300_set_key_cache_entry_mac ; 
 int /*<<< orphan*/  ar9300_set_led_state ; 
 int /*<<< orphan*/  ar9300_set_mac_address ; 
 int /*<<< orphan*/  ar9300_set_multicast_filter ; 
 int /*<<< orphan*/  ar9300_set_pcu_config ; 
 int /*<<< orphan*/  ar9300_set_power_mode ; 
 int /*<<< orphan*/  ar9300_set_quiet ; 
 int /*<<< orphan*/  ar9300_set_regulatory_domain ; 
 int /*<<< orphan*/  ar9300_set_rx_dp ; 
 int /*<<< orphan*/  ar9300_set_rx_filter ; 
 int /*<<< orphan*/  ar9300_set_slot_time ; 
 int /*<<< orphan*/  ar9300_set_sta_beacon_timers ; 
 int /*<<< orphan*/  ar9300_set_tx_dp ; 
 int /*<<< orphan*/  ar9300_set_tx_queue_props ; 
 int /*<<< orphan*/  ar9300_setup_tx_queue ; 
 int /*<<< orphan*/  ar9300_setup_tx_status_ring ; 
 int /*<<< orphan*/  ar9300_start_pcu_receive ; 
 int /*<<< orphan*/  ar9300_start_spectral_scan ; 
 int /*<<< orphan*/  ar9300_start_tx_dma ; 
 int /*<<< orphan*/  ar9300_stop_dma_receive_freebsd ; 
 int /*<<< orphan*/  ar9300_stop_pcu_receive ; 
 int /*<<< orphan*/  ar9300_stop_spectral_scan ; 
 int /*<<< orphan*/  ar9300_stop_tx_dma_freebsd ; 
 int /*<<< orphan*/  ar9300_update_tx_trig_level ; 
 int /*<<< orphan*/  ar9300_write_associd ; 
 int /*<<< orphan*/  ath_hal_getChanNoise ; 

void
ar9300_attach_freebsd_ops(struct ath_hal *ah)
{

	/* Global functions */
	ah->ah_detach		= ar9300_detach;
	ah->ah_getRateTable		= ar9300_get_rate_table;

	/* Reset functions */
	ah->ah_reset		= ar9300_reset_freebsd;
	ah->ah_phyDisable		= ar9300_phy_disable;
	ah->ah_disable		= ar9300_disable;
	ah->ah_configPCIE		= ar9300_config_pcie_freebsd;
//	ah->ah_disablePCIE		= ar9300_disable_pcie_phy;
	ah->ah_setPCUConfig		= ar9300_set_pcu_config;
	// perCalibration
	ah->ah_perCalibrationN	= ar9300_per_calibration_freebsd;
	ah->ah_resetCalValid	= ar9300_reset_cal_valid_freebsd;
	ah->ah_setTxPowerLimit	= ar9300_freebsd_set_tx_power_limit;
	ah->ah_getChanNoise		= ath_hal_getChanNoise;

	/* Transmit functions */
	ah->ah_setupTxQueue		= ar9300_setup_tx_queue;
	ah->ah_setTxQueueProps	= ar9300_set_tx_queue_props;
	ah->ah_getTxQueueProps	= ar9300_get_tx_queue_props;
	ah->ah_releaseTxQueue	= ar9300_release_tx_queue;
	ah->ah_resetTxQueue		= ar9300_reset_tx_queue;
	ah->ah_getTxDP		= ar9300_get_tx_dp;
	ah->ah_setTxDP		= ar9300_set_tx_dp;
	ah->ah_numTxPending		= ar9300_num_tx_pending;
	ah->ah_startTxDma		= ar9300_start_tx_dma;
	ah->ah_stopTxDma		= ar9300_stop_tx_dma_freebsd;
	ah->ah_setupTxDesc		= ar9300_freebsd_setup_tx_desc;
	ah->ah_setupXTxDesc		= ar9300_freebsd_setup_x_tx_desc;
	ah->ah_fillTxDesc		= ar9300_freebsd_fill_tx_desc;
	ah->ah_procTxDesc		= ar9300_freebsd_proc_tx_desc;
	ah->ah_getTxIntrQueue	= ar9300_get_tx_intr_queue;
	// reqTxIntrDesc
	ah->ah_getTxCompletionRates	= ar9300_freebsd_get_tx_completion_rates;
	ah->ah_setTxDescLink	= ar9300_set_desc_link;
	ah->ah_getTxDescLink	= ar9300_freebsd_get_desc_link;
	ah->ah_getTxDescLinkPtr	= ar9300_get_desc_link_ptr;
	ah->ah_setupTxStatusRing	= ar9300_setup_tx_status_ring;
	ah->ah_getTxRawTxDesc	 = ar9300_get_raw_tx_desc;
	ah->ah_updateTxTrigLevel	= ar9300_update_tx_trig_level;

	/* RX functions */
	ah->ah_getRxDP		= ar9300_get_rx_dp;
	ah->ah_setRxDP		= ar9300_set_rx_dp;
	ah->ah_enableReceive	= ar9300_enable_receive;
	ah->ah_stopDmaReceive	= ar9300_stop_dma_receive_freebsd;
	ah->ah_startPcuReceive	= ar9300_start_pcu_receive;
	ah->ah_stopPcuReceive	= ar9300_stop_pcu_receive;
	ah->ah_setMulticastFilter	= ar9300_set_multicast_filter;
	ah->ah_setMulticastFilterIndex = ar9300SetMulticastFilterIndex;
	ah->ah_clrMulticastFilterIndex = ar9300ClrMulticastFilterIndex;
	ah->ah_getRxFilter		= ar9300_get_rx_filter;
	ah->ah_setRxFilter		= ar9300_set_rx_filter;
	/* setupRxDesc */
	ah->ah_procRxDesc		= ar9300_proc_rx_desc_freebsd;
	ah->ah_rxMonitor		= ar9300_ani_rxmonitor_freebsd;
	ah->ah_aniPoll		= ar9300_ani_poll_freebsd;
	ah->ah_procMibEvent		= ar9300_process_mib_intr;

	/* Misc functions */
	ah->ah_getCapability	= ar9300_get_capability;
	ah->ah_setCapability	= ar9300_set_capability;
	ah->ah_getDiagState		= ar9300_get_diag_state;
	ah->ah_getMacAddress	= ar9300_get_mac_address;
	ah->ah_setMacAddress	= ar9300_set_mac_address;
	ah->ah_getBssIdMask		= ar9300_get_bss_id_mask;
	ah->ah_setBssIdMask		= ar9300_set_bss_id_mask;
	ah->ah_setRegulatoryDomain	= ar9300_set_regulatory_domain;
	ah->ah_setLedState		= ar9300_set_led_state;
	ah->ah_writeAssocid		= ar9300_write_associd;
	ah->ah_gpioCfgInput		= ar9300_gpio_cfg_input;
	ah->ah_gpioCfgOutput	= ar9300_gpio_cfg_output;
	ah->ah_gpioGet		= ar9300_gpio_get;
	ah->ah_gpioSet		= ar9300_gpio_set;
	ah->ah_gpioSetIntr		= ar9300_gpio_set_intr;
	/* polarity */
	/* mask */
	ah->ah_getTsf32		= ar9300_get_tsf32;
	ah->ah_getTsf64		= ar9300_get_tsf64;
	ah->ah_resetTsf		= ar9300_reset_tsf;
	ah->ah_setTsf64		= ar9300_freebsd_set_tsf64;
	ah->ah_detectCardPresent	= ar9300_detect_card_present;
	// ah->ah_updateMibCounters	= ar9300_update_mib_counters;
	ah->ah_getRfGain		= ar9300_get_rfgain;
	ah->ah_getDefAntenna	= ar9300_get_def_antenna;
	ah->ah_setDefAntenna	= ar9300_set_def_antenna;
	ah->ah_getAntennaSwitch	= ar9300_freebsd_get_antenna_switch;
	ah->ah_setAntennaSwitch	= ar9300_freebsd_set_antenna_switch;
	// ah->ah_setSifsTime		= ar9300_set_sifs_time;
	// ah->ah_getSifsTime		= ar9300_get_sifs_time;
	ah->ah_setSlotTime		= ar9300_set_slot_time;
	ah->ah_getSlotTime		= ar9300GetSlotTime;
	ah->ah_getAckTimeout	= ar9300_get_ack_timeout;
	ah->ah_setAckTimeout	= ar9300_set_ack_timeout;
	// XXX ack/ctsrate
	// XXX CTS timeout
	ah->ah_getCTSTimeout = ar9300_freebsd_get_cts_timeout;
	// XXX decompmask
	// coverageclass
	ah->ah_setQuiet		= ar9300_set_quiet;
	ah->ah_getMibCycleCounts	= ar9300_freebsd_get_mib_cycle_counts;

	/* DFS functions */
	ah->ah_enableDfs		= ar9300_enable_dfs;
	ah->ah_getDfsThresh		= ar9300_get_dfs_thresh;
	ah->ah_getDfsDefaultThresh	= ar9300_get_default_dfs_thresh;
	ah->ah_procRadarEvent		= ar9300_freebsd_proc_radar_event;
	ah->ah_isFastClockEnabled	= ar9300_is_fast_clock_enabled;
	ah->ah_get11nExtBusy		= ar9300_get_11n_ext_busy;
	ah->ah_setDfsCacTxQuiet		= ar9300_cac_tx_quiet;

	/* Spectral Scan Functions */
	ah->ah_spectralConfigure	= ar9300_configure_spectral_scan;
	ah->ah_spectralGetConfig	= ar9300_get_spectral_params;
	ah->ah_spectralStart		= ar9300_start_spectral_scan;
	ah->ah_spectralStop		= ar9300_stop_spectral_scan;
	ah->ah_spectralIsEnabled	= ar9300_is_spectral_enabled;
	ah->ah_spectralIsActive		= ar9300_is_spectral_active;

	/* Key cache functions */
	ah->ah_getKeyCacheSize	= ar9300_get_key_cache_size;
	ah->ah_resetKeyCacheEntry	= ar9300_reset_key_cache_entry;
	ah->ah_isKeyCacheEntryValid	= ar9300_is_key_cache_entry_valid;
	ah->ah_setKeyCacheEntry	= ar9300_set_key_cache_entry;
	ah->ah_setKeyCacheEntryMac	= ar9300_set_key_cache_entry_mac;

	/* Power management functions */
	ah->ah_setPowerMode		= ar9300_set_power_mode;
	ah->ah_getPowerMode		= ar9300_get_power_mode;

	/* Beacon functions */
	/* ah_setBeaconTimers */
	ah->ah_beaconInit		= ar9300_freebsd_beacon_init;
	ah->ah_setBeaconTimers		= ar9300_beacon_set_beacon_timers;
	ah->ah_setStationBeaconTimers = ar9300_set_sta_beacon_timers;
	/* ah_resetStationBeaconTimers */
	ah->ah_getNextTBTT = ar9300_get_next_tbtt;

	/* Interrupt functions */
	ah->ah_isInterruptPending	= ar9300_is_interrupt_pending;
	ah->ah_getPendingInterrupts	= ar9300_get_pending_interrupts_freebsd;
	ah->ah_getInterrupts =	ar9300_get_interrupts;
	ah->ah_setInterrupts =	ar9300_set_interrupts_freebsd;

	/* Regulatory/internal functions */
	//    AH_PRIVATE(ah)->ah_getNfAdjust = ar9300_get_nf_adjust;
	AH_PRIVATE(ah)->ah_eepromRead = ar9300_eeprom_read_word;
	//    AH_PRIVATE(ah)->ah_getChipPowerLimits = ar9300_get_chip_power_limits;
	AH_PRIVATE(ah)->ah_getWirelessModes = ar9300_get_wireless_modes;
	AH_PRIVATE(ah)->ah_getChannelEdges = ar9300_get_channel_edges;

	AH_PRIVATE(ah)->ah_eepromRead = ar9300_eeprom_read_word;
	/* XXX ah_eeprom */
	/* XXX ah_eeversion */
	/* XXX ah_eepromDetach */
	/* XXX ah_eepromGet */
	AH_PRIVATE(ah)->ah_eepromGet = ar9300_eeprom_get_freebsd;
	/* XXX ah_eepromSet */
	/* XXX ah_getSpurChan */
	/* XXX ah_eepromDiag */

	/* 802.11n functions */
	ah->ah_chainTxDesc = ar9300_freebsd_chain_tx_desc;
	ah->ah_setupFirstTxDesc= ar9300_freebsd_setup_first_tx_desc;
	ah->ah_setupLastTxDesc = ar9300_freebsd_setup_last_tx_desc;
	ah->ah_set11nRateScenario = ar9300_freebsd_set_11n_rate_scenario;
	ah->ah_set11nTxDesc = ar9300_freebsd_setup_11n_desc;
	ah->ah_set11nAggrFirst = ar9300_set_11n_aggr_first;
	ah->ah_set11nAggrMiddle = ar9300_set_11n_aggr_middle;
	ah->ah_set11nAggrLast = ar9300_set_11n_aggr_last;
	ah->ah_clr11nAggr = ar9300_clr_11n_aggr;
	ah->ah_set11nBurstDuration = ar9300_set_11n_burst_duration;
	/* ah_get11nExtBusy */
	ah->ah_set11nMac2040 = ar9300_set_11n_mac2040;
	ah->ah_setChainMasks = ar9300SetChainMasks;
	/* ah_get11nRxClear */
	/* ah_set11nRxClear */

	/* bluetooth coexistence functions */
	ah->ah_btCoexSetInfo		= ar9300_set_bt_coex_info;
	ah->ah_btCoexSetConfig		= ar9300_bt_coex_config;
	ah->ah_btCoexSetQcuThresh	= ar9300_bt_coex_set_qcu_thresh;
	ah->ah_btCoexSetWeights		= ar9300_bt_coex_set_weights;
	ah->ah_btCoexSetBmissThresh	= ar9300_bt_coex_setup_bmiss_thresh;
	ah->ah_btCoexSetParameter	= ar9300_bt_coex_set_parameter;
	ah->ah_btCoexDisable		= ar9300_bt_coex_disable;
	ah->ah_btCoexEnable		= ar9300_bt_coex_enable;

	/* MCI bluetooth functions */
	if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
		/*
		 * Note: these are done in attach too for now, because
		 * at this point we haven't yet setup the mac/bb revision
		 * values, so this code is effectively NULL.
		 * However, I'm leaving this here so people digging
		 * into the code (a) see the MCI bits here, and (b)
		 * are now told they should look elsewhere for
		 * these methods.
		 */
		ah->ah_btCoexSetWeights = ar9300_mci_bt_coex_set_weights;
		ah->ah_btCoexDisable = ar9300_mci_bt_coex_disable;
		ah->ah_btCoexEnable = ar9300_mci_bt_coex_enable;
	}
	ah->ah_btMciSetup		= ar9300_mci_setup;
	ah->ah_btMciSendMessage		= ar9300_mci_send_message;
	ah->ah_btMciGetInterrupt	= ar9300_mci_get_interrupt;
	ah->ah_btMciState		= ar9300_mci_state;
	ah->ah_btMciDetach		= ar9300_mci_detach;

	/* LNA diversity functions */
	ah->ah_divLnaConfGet = ar9300_ant_div_comb_get_config;
	ah->ah_divLnaConfSet = ar9300_ant_div_comb_set_config;
}