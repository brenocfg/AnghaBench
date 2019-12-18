#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct an_req {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_ltv_stats {int an_rx_overruns; int an_rx_plcp_csum_errs; int an_rx_plcp_format_errs; int an_rx_plcp_len_errs; int an_rx_mac_crc_errs; int an_rx_mac_crc_ok; int an_rx_wep_errs; int an_rx_wep_ok; int an_retry_long; int an_retry_short; int an_retry_max; int an_no_ack; int an_no_cts; int an_rx_ack_ok; int an_rx_cts_ok; int an_tx_ack_ok; int an_tx_rts_ok; int an_tx_cts_ok; int an_tx_lmac_mcasts; int an_tx_lmac_bcasts; int an_tx_lmac_ucast_frags; int an_tx_lmac_ucasts; int an_tx_beacons; int an_rx_beacons; int an_tx_single_cols; int an_tx_multi_cols; int an_tx_defers_no; int an_tx_defers_prot; int an_tx_defers_energy; int an_rx_dups; int an_rx_partial; int an_tx_too_old; int an_lostsync_missed_beacons; int an_lostsync_arl_exceeded; int an_lostsync_deauthed; int an_lostsync_disassociated; int an_lostsync_tsf_timing; int an_tx_host_mcasts; int an_tx_host_bcasts; int an_tx_host_ucasts; int an_tx_host_failed; int an_rx_host_mcasts; int an_rx_host_bcasts; int an_rx_host_ucasts; int an_rx_host_discarded; int an_tx_hmac_mcasts; int an_tx_hmac_bcasts; int an_tx_hmac_ucasts; int an_tx_hmac_failed; int an_rx_hmac_mcasts; int an_rx_hmac_bcasts; int an_rx_hmac_ucasts; int an_rx_hmac_discarded; int an_tx_hmac_accepted; int an_ssid_mismatches; int an_ap_mismatches; int an_rates_mismatches; int an_auth_rejects; int an_auth_timeouts; int an_assoc_rejects; int an_assoc_timeouts; int an_rx_mgmt_pkts; int an_tx_mgmt_pkts; int an_rx_refresh_pkts; int an_tx_refresh_pkts; int an_rx_poll_pkts; int an_tx_poll_pkts; int an_lostsync_hostreq; int an_host_tx_bytes; int an_host_rx_bytes; int an_uptime_usecs; int an_uptime_secs; int an_lostsync_better_ap; } ;
typedef  int /*<<< orphan*/  areq ;

/* Variables and functions */
 int /*<<< orphan*/  AN_RID_32BITS_CUM ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
an_dumpstats(const char *iface)
{
	struct an_ltv_stats	*stats;
	struct an_req		areq;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_32BITS_CUM;

	an_getval(iface, &areq);

	stats = (struct an_ltv_stats *)((uint16_t *)&areq - 1);

	printf("RX overruns:\t\t\t\t\t[ %u ]\n", stats->an_rx_overruns);
	printf("RX PLCP CSUM errors:\t\t\t\t[ %u ]\n",
	    stats->an_rx_plcp_csum_errs);
	printf("RX PLCP format errors:\t\t\t\t[ %u ]\n",
	    stats->an_rx_plcp_format_errs);
	printf("RX PLCP length errors:\t\t\t\t[ %u ]\n",
	    stats->an_rx_plcp_len_errs);
	printf("RX MAC CRC errors:\t\t\t\t[ %u ]\n",
	    stats->an_rx_mac_crc_errs);
	printf("RX MAC CRC OK:\t\t\t\t\t[ %u ]\n",
	    stats->an_rx_mac_crc_ok);
	printf("RX WEP errors:\t\t\t\t\t[ %u ]\n",
	    stats->an_rx_wep_errs);
	printf("RX WEP OK:\t\t\t\t\t[ %u ]\n",
	    stats->an_rx_wep_ok);
	printf("Long retries:\t\t\t\t\t[ %u ]\n",
	    stats->an_retry_long);
	printf("Short retries:\t\t\t\t\t[ %u ]\n",
	    stats->an_retry_short);
	printf("Retries exhausted:\t\t\t\t[ %u ]\n",
	    stats->an_retry_max);
	printf("Bad ACK:\t\t\t\t\t[ %u ]\n",
	    stats->an_no_ack);
	printf("Bad CTS:\t\t\t\t\t[ %u ]\n",
	    stats->an_no_cts);
	printf("RX good ACKs:\t\t\t\t\t[ %u ]\n",
	    stats->an_rx_ack_ok);
	printf("RX good CTSs:\t\t\t\t\t[ %u ]\n",
	    stats->an_rx_cts_ok);
	printf("TX good ACKs:\t\t\t\t\t[ %u ]\n",
	    stats->an_tx_ack_ok);
	printf("TX good RTSs:\t\t\t\t\t[ %u ]\n",
	    stats->an_tx_rts_ok);
	printf("TX good CTSs:\t\t\t\t\t[ %u ]\n",
	    stats->an_tx_cts_ok);
	printf("LMAC multicasts transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_lmac_mcasts);
	printf("LMAC broadcasts transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_lmac_bcasts);
	printf("LMAC unicast frags transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_lmac_ucast_frags);
	printf("LMAC unicasts transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_lmac_ucasts);
	printf("Beacons transmitted:\t\t\t\t[ %u ]\n",
	    stats->an_tx_beacons);
	printf("Beacons received:\t\t\t\t[ %u ]\n",
	    stats->an_rx_beacons);
	printf("Single transmit collisions:\t\t\t[ %u ]\n",
	    stats->an_tx_single_cols);
	printf("Multiple transmit collisions:\t\t\t[ %u ]\n",
	    stats->an_tx_multi_cols);
	printf("Transmits without deferrals:\t\t\t[ %u ]\n",
	    stats->an_tx_defers_no);
	printf("Transmits deferred due to protocol:\t\t[ %u ]\n",
	    stats->an_tx_defers_prot);
	printf("Transmits deferred due to energy detect:\t\t[ %u ]\n",
	    stats->an_tx_defers_energy);
	printf("RX duplicate frames/frags:\t\t\t[ %u ]\n",
	    stats->an_rx_dups);
	printf("RX partial frames:\t\t\t\t[ %u ]\n",
	    stats->an_rx_partial);
	printf("TX max lifetime exceeded:\t\t\t[ %u ]\n",
	    stats->an_tx_too_old);
	printf("RX max lifetime exceeded:\t\t\t[ %u ]\n",
	    stats->an_tx_too_old);
	printf("Sync lost due to too many missed beacons:\t[ %u ]\n",
	    stats->an_lostsync_missed_beacons);
	printf("Sync lost due to ARL exceeded:\t\t\t[ %u ]\n",
	    stats->an_lostsync_arl_exceeded);
	printf("Sync lost due to deauthentication:\t\t[ %u ]\n",
	    stats->an_lostsync_deauthed);
	printf("Sync lost due to disassociation:\t\t[ %u ]\n",
	    stats->an_lostsync_disassociated);
	printf("Sync lost due to excess change in TSF timing:\t[ %u ]\n",
	    stats->an_lostsync_tsf_timing);
	printf("Host transmitted multicasts:\t\t\t[ %u ]\n",
	    stats->an_tx_host_mcasts);
	printf("Host transmitted broadcasts:\t\t\t[ %u ]\n",
	    stats->an_tx_host_bcasts);
	printf("Host transmitted unicasts:\t\t\t[ %u ]\n",
	    stats->an_tx_host_ucasts);
	printf("Host transmission failures:\t\t\t[ %u ]\n",
	    stats->an_tx_host_failed);
	printf("Host received multicasts:\t\t\t[ %u ]\n",
	    stats->an_rx_host_mcasts);
	printf("Host received broadcasts:\t\t\t[ %u ]\n",
	    stats->an_rx_host_bcasts);
	printf("Host received unicasts:\t\t\t\t[ %u ]\n",
	    stats->an_rx_host_ucasts);
	printf("Host receive discards:\t\t\t\t[ %u ]\n",
	    stats->an_rx_host_discarded);
	printf("HMAC transmitted multicasts:\t\t\t[ %u ]\n",
	    stats->an_tx_hmac_mcasts);
	printf("HMAC transmitted broadcasts:\t\t\t[ %u ]\n",
	    stats->an_tx_hmac_bcasts);
	printf("HMAC transmitted unicasts:\t\t\t[ %u ]\n",
	    stats->an_tx_hmac_ucasts);
	printf("HMAC transmissions failed:\t\t\t[ %u ]\n",
	    stats->an_tx_hmac_failed);
	printf("HMAC received multicasts:\t\t\t[ %u ]\n",
	    stats->an_rx_hmac_mcasts);
	printf("HMAC received broadcasts:\t\t\t[ %u ]\n",
	    stats->an_rx_hmac_bcasts);
	printf("HMAC received unicasts:\t\t\t\t[ %u ]\n",
	    stats->an_rx_hmac_ucasts);
	printf("HMAC receive discards:\t\t\t\t[ %u ]\n",
	    stats->an_rx_hmac_discarded);
	printf("HMAC transmits accepted:\t\t\t[ %u ]\n",
	    stats->an_tx_hmac_accepted);
	printf("SSID mismatches:\t\t\t\t[ %u ]\n",
	    stats->an_ssid_mismatches);
	printf("Access point mismatches:\t\t\t[ %u ]\n",
	    stats->an_ap_mismatches);
	printf("Speed mismatches:\t\t\t\t[ %u ]\n",
	    stats->an_rates_mismatches);
	printf("Authentication rejects:\t\t\t\t[ %u ]\n",
	    stats->an_auth_rejects);
	printf("Authentication timeouts:\t\t\t[ %u ]\n",
	    stats->an_auth_timeouts);
	printf("Association rejects:\t\t\t\t[ %u ]\n",
	    stats->an_assoc_rejects);
	printf("Association timeouts:\t\t\t\t[ %u ]\n",
	    stats->an_assoc_timeouts);
	printf("Management frames received:\t\t\t[ %u ]\n",
	    stats->an_rx_mgmt_pkts);
	printf("Management frames transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_mgmt_pkts);
	printf("Refresh frames received:\t\t\t[ %u ]\n",
	    stats->an_rx_refresh_pkts);
	printf("Refresh frames transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_refresh_pkts);
	printf("Poll frames received:\t\t\t\t[ %u ]\n",
	    stats->an_rx_poll_pkts);
	printf("Poll frames transmitted:\t\t\t[ %u ]\n",
	    stats->an_tx_poll_pkts);
	printf("Host requested sync losses:\t\t\t[ %u ]\n",
	    stats->an_lostsync_hostreq);
	printf("Host transmitted bytes:\t\t\t\t[ %u ]\n",
	    stats->an_host_tx_bytes);
	printf("Host received bytes:\t\t\t\t[ %u ]\n",
	    stats->an_host_rx_bytes);
	printf("Uptime in microseconds:\t\t\t\t[ %u ]\n",
	    stats->an_uptime_usecs);
	printf("Uptime in seconds:\t\t\t\t[ %u ]\n",
	    stats->an_uptime_secs);
	printf("Sync lost due to better AP:\t\t\t[ %u ]\n",
	    stats->an_lostsync_better_ap);
}