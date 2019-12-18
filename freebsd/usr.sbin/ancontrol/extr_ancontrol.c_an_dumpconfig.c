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
struct an_req {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_ltv_genconfig {int an_opmode; int an_rxmode; scalar_t__ an_devtype; scalar_t__ an_scanmode; int an_authtype; scalar_t__ an_psave_mode; int an_radiotype; int an_diversity; int an_home_product; int /*<<< orphan*/  an_arl_delay; int /*<<< orphan*/  an_arl_decay; int /*<<< orphan*/  an_arl_thresh; int /*<<< orphan*/  an_nodename; int /*<<< orphan*/  an_rss_thresh; int /*<<< orphan*/  an_tx_power; int /*<<< orphan*/  an_dtim_period; int /*<<< orphan*/  an_ds_channel; int /*<<< orphan*/  an_atim_duration; int /*<<< orphan*/  an_beacon_period; int /*<<< orphan*/  an_fast_listen_decay; int /*<<< orphan*/  an_listen_decay; int /*<<< orphan*/  an_fast_listen_interval; int /*<<< orphan*/  an_listen_interval; int /*<<< orphan*/  an_sleep_for_dtims; int /*<<< orphan*/  an_refresh_interval; int /*<<< orphan*/  an_max_beacon_lost_time; int /*<<< orphan*/  an_link_loss_delay; int /*<<< orphan*/  an_offline_scan_duration; int /*<<< orphan*/  an_offline_scan_interval; int /*<<< orphan*/  an_specified_ap_timeout; int /*<<< orphan*/  an_assoc_timeout; int /*<<< orphan*/  an_auth_timeout; int /*<<< orphan*/  an_ibss_join_net_timeout; int /*<<< orphan*/  an_beacon_listen_timeout; int /*<<< orphan*/  an_probe_response_timeout; int /*<<< orphan*/  an_probe_energy_timeout; int /*<<< orphan*/  an_probedelay; int /*<<< orphan*/  an_ordering; int /*<<< orphan*/  an_stationary; int /*<<< orphan*/  an_rx_msdu_lifetime; int /*<<< orphan*/  an_tx_msdu_lifetime; int /*<<< orphan*/  an_longretry_limit; int /*<<< orphan*/  an_shortretry_limit; int /*<<< orphan*/  an_rates; int /*<<< orphan*/  an_macaddr; int /*<<< orphan*/  an_rtsthresh; int /*<<< orphan*/  an_fragthresh; } ;
typedef  int /*<<< orphan*/  areq ;

/* Variables and functions */
 int AN_AUTHTYPE_ALLOW_UNENCRYPTED ; 
 int AN_AUTHTYPE_LEAP ; 
 int AN_AUTHTYPE_MASK ; 
 int AN_AUTHTYPE_NONE ; 
 int AN_AUTHTYPE_OPEN ; 
 int AN_AUTHTYPE_PRIVACY_IN_USE ; 
 int AN_AUTHTYPE_SHAREDKEY ; 
 scalar_t__ AN_DEVTYPE_PC4500 ; 
 scalar_t__ AN_DEVTYPE_PC4800 ; 
 unsigned char AN_DIVERSITY_ANTENNA_1_AND_2 ; 
 unsigned char AN_DIVERSITY_ANTENNA_1_ONLY ; 
 unsigned char AN_DIVERSITY_ANTENNA_2_ONLY ; 
 unsigned char AN_DIVERSITY_FACTORY_DEFAULT ; 
 int AN_HOME_NETWORK ; 
 int AN_OPMODE_AP ; 
 int AN_OPMODE_AP_REPEATER ; 
 int AN_OPMODE_IBSS_ADHOC ; 
 int AN_OPMODE_INFRASTRUCTURE_STATION ; 
 scalar_t__ AN_PSAVE_CAM ; 
 scalar_t__ AN_PSAVE_NONE ; 
 scalar_t__ AN_PSAVE_PSP ; 
 scalar_t__ AN_PSAVE_PSP_CAM ; 
 int AN_RADIOTYPE_80211_DS ; 
 int AN_RADIOTYPE_80211_FH ; 
 int AN_RADIOTYPE_LM2000_DS ; 
 int /*<<< orphan*/  AN_RID_ACTUALCFG ; 
 int AN_RXMODE_80211_MONITOR_ANYBSS ; 
 int AN_RXMODE_80211_MONITOR_CURBSS ; 
 int AN_RXMODE_ADDR ; 
 int AN_RXMODE_BC_ADDR ; 
 int AN_RXMODE_BC_MC_ADDR ; 
 int AN_RXMODE_LAN_MONITOR_CURBSS ; 
 scalar_t__ AN_SCANMODE_ACTIVE ; 
 scalar_t__ AN_SCANMODE_AIRONET_ACTIVE ; 
 scalar_t__ AN_SCANMODE_PASSIVE ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  an_printbool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_printhex (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  an_printspeeds (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  an_printstr (char*,int) ; 
 int /*<<< orphan*/  an_printwords (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  an_readkeyinfo (char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
an_dumpconfig(const char *iface)
{
	struct an_ltv_genconfig	*cfg;
	struct an_req		areq;
	unsigned char		diversity;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_ACTUALCFG;

	an_getval(iface, &areq);

	cfg = (struct an_ltv_genconfig *)&areq;

	printf("Operating mode:\t\t\t\t[ ");
	if ((cfg->an_opmode & 0x7) == AN_OPMODE_IBSS_ADHOC)
		printf("ad-hoc");
	if ((cfg->an_opmode & 0x7) == AN_OPMODE_INFRASTRUCTURE_STATION)
		printf("infrastructure");
	if ((cfg->an_opmode & 0x7) == AN_OPMODE_AP)
		printf("access point");
	if ((cfg->an_opmode & 0x7) == AN_OPMODE_AP_REPEATER)
		printf("access point repeater");
	printf(" ]");
	printf("\nReceive mode:\t\t\t\t[ ");
	if ((cfg->an_rxmode & 0x7) == AN_RXMODE_BC_MC_ADDR)
		printf("broadcast/multicast/unicast");
	if ((cfg->an_rxmode & 0x7) == AN_RXMODE_BC_ADDR)
		printf("broadcast/unicast");
	if ((cfg->an_rxmode & 0x7) == AN_RXMODE_ADDR)
		printf("unicast");
	if ((cfg->an_rxmode & 0x7) == AN_RXMODE_80211_MONITOR_CURBSS)
		printf("802.11 monitor, current BSSID");
	if ((cfg->an_rxmode & 0x7) == AN_RXMODE_80211_MONITOR_ANYBSS)
		printf("802.11 monitor, any BSSID");
	if ((cfg->an_rxmode & 0x7) == AN_RXMODE_LAN_MONITOR_CURBSS)
		printf("LAN monitor, current BSSID");
	printf(" ]");
	printf("\nFragment threshold:\t\t\t");
	an_printwords(&cfg->an_fragthresh, 1);
	printf("\nRTS threshold:\t\t\t\t");
	an_printwords(&cfg->an_rtsthresh, 1);
	printf("\nMAC address:\t\t\t\t");
	an_printhex((char *)&cfg->an_macaddr, ETHER_ADDR_LEN);
	printf("\nSupported rates:\t\t\t");
	an_printspeeds(cfg->an_rates, 8);
	printf("\nShort retry limit:\t\t\t");
	an_printwords(&cfg->an_shortretry_limit, 1);
	printf("\nLong retry limit:\t\t\t");
	an_printwords(&cfg->an_longretry_limit, 1);
	printf("\nTX MSDU lifetime:\t\t\t");
	an_printwords(&cfg->an_tx_msdu_lifetime, 1);
	printf("\nRX MSDU lifetime:\t\t\t");
	an_printwords(&cfg->an_rx_msdu_lifetime, 1);
	printf("\nStationary:\t\t\t\t");
	an_printbool(cfg->an_stationary);
	printf("\nOrdering:\t\t\t\t");
	an_printbool(cfg->an_ordering);
	printf("\nDevice type:\t\t\t\t[ ");
	if (cfg->an_devtype == AN_DEVTYPE_PC4500)
		printf("PC4500");
	else if (cfg->an_devtype == AN_DEVTYPE_PC4800)
		printf("PC4800");
	else
		printf("unknown (%x)", cfg->an_devtype);
	printf(" ]");
	printf("\nScanning mode:\t\t\t\t[ ");
	if (cfg->an_scanmode == AN_SCANMODE_ACTIVE)
		printf("active");
	if (cfg->an_scanmode == AN_SCANMODE_PASSIVE)
		printf("passive");
	if (cfg->an_scanmode == AN_SCANMODE_AIRONET_ACTIVE)
		printf("Aironet active");
	printf(" ]");
	printf("\nProbe delay:\t\t\t\t");
	an_printwords(&cfg->an_probedelay, 1);
	printf("\nProbe energy timeout:\t\t\t");
	an_printwords(&cfg->an_probe_energy_timeout, 1);
	printf("\nProbe response timeout:\t\t\t");
	an_printwords(&cfg->an_probe_response_timeout, 1);
	printf("\nBeacon listen timeout:\t\t\t");
	an_printwords(&cfg->an_beacon_listen_timeout, 1);
	printf("\nIBSS join network timeout:\t\t");
	an_printwords(&cfg->an_ibss_join_net_timeout, 1);
	printf("\nAuthentication timeout:\t\t\t");
	an_printwords(&cfg->an_auth_timeout, 1);
	printf("\nWEP enabled:\t\t\t\t[ ");
	if (cfg->an_authtype & AN_AUTHTYPE_PRIVACY_IN_USE)
	{
		if (cfg->an_authtype & AN_AUTHTYPE_LEAP)
			 printf("LEAP");
		else if (cfg->an_authtype & AN_AUTHTYPE_ALLOW_UNENCRYPTED)
			 printf("mixed cell");
		else
			 printf("full");
	}
	else
		printf("no");
	printf(" ]");
	printf("\nAuthentication type:\t\t\t[ ");
	if ((cfg->an_authtype & AN_AUTHTYPE_MASK) == AN_AUTHTYPE_NONE)
		printf("none");
	if ((cfg->an_authtype & AN_AUTHTYPE_MASK) == AN_AUTHTYPE_OPEN)
		printf("open");
	if ((cfg->an_authtype & AN_AUTHTYPE_MASK) == AN_AUTHTYPE_SHAREDKEY)
		printf("shared key");
	printf(" ]");
	printf("\nAssociation timeout:\t\t\t");
	an_printwords(&cfg->an_assoc_timeout, 1);
	printf("\nSpecified AP association timeout:\t");
	an_printwords(&cfg->an_specified_ap_timeout, 1);
	printf("\nOffline scan interval:\t\t\t");
	an_printwords(&cfg->an_offline_scan_interval, 1);
	printf("\nOffline scan duration:\t\t\t");
	an_printwords(&cfg->an_offline_scan_duration, 1);
	printf("\nLink loss delay:\t\t\t");
	an_printwords(&cfg->an_link_loss_delay, 1);
	printf("\nMax beacon loss time:\t\t\t");
	an_printwords(&cfg->an_max_beacon_lost_time, 1);
	printf("\nRefresh interval:\t\t\t");
	an_printwords(&cfg->an_refresh_interval, 1);
	printf("\nPower save mode:\t\t\t[ ");
	if (cfg->an_psave_mode == AN_PSAVE_NONE)
		printf("none");
	if (cfg->an_psave_mode == AN_PSAVE_CAM)
		printf("constantly awake mode");
	if (cfg->an_psave_mode == AN_PSAVE_PSP)
		printf("PSP");
	if (cfg->an_psave_mode == AN_PSAVE_PSP_CAM)
		printf("PSP-CAM (fast PSP)");
	printf(" ]");
	printf("\nSleep through DTIMs:\t\t\t");
	an_printbool(cfg->an_sleep_for_dtims);
	printf("\nPower save listen interval:\t\t");
	an_printwords(&cfg->an_listen_interval, 1);
	printf("\nPower save fast listen interval:\t");
	an_printwords(&cfg->an_fast_listen_interval, 1);
	printf("\nPower save listen decay:\t\t");
	an_printwords(&cfg->an_listen_decay, 1);
	printf("\nPower save fast listen decay:\t\t");
	an_printwords(&cfg->an_fast_listen_decay, 1);
	printf("\nAP/ad-hoc Beacon period:\t\t");
	an_printwords(&cfg->an_beacon_period, 1);
	printf("\nAP/ad-hoc ATIM duration:\t\t");
	an_printwords(&cfg->an_atim_duration, 1);
	printf("\nAP/ad-hoc current channel:\t\t");
	an_printwords(&cfg->an_ds_channel, 1);
	printf("\nAP/ad-hoc DTIM period:\t\t\t");
	an_printwords(&cfg->an_dtim_period, 1);
	printf("\nRadio type:\t\t\t\t[ ");
	if (cfg->an_radiotype & AN_RADIOTYPE_80211_FH)
		printf("802.11 FH");
	else if (cfg->an_radiotype & AN_RADIOTYPE_80211_DS)
		printf("802.11 DS");
	else if (cfg->an_radiotype & AN_RADIOTYPE_LM2000_DS)
		printf("LM2000 DS");
	else
		printf("unknown (%x)", cfg->an_radiotype);
	printf(" ]");
	printf("\nRX Diversity:\t\t\t\t[ ");
	diversity = cfg->an_diversity & 0xFF;
	if (diversity == AN_DIVERSITY_FACTORY_DEFAULT)
		printf("factory default");
	else if (diversity == AN_DIVERSITY_ANTENNA_1_ONLY)
		printf("antenna 1 only");
	else if (diversity == AN_DIVERSITY_ANTENNA_2_ONLY)
		printf("antenna 2 only");
	else if (diversity == AN_DIVERSITY_ANTENNA_1_AND_2)
		printf("antenna 1 and 2");
	printf(" ]");
	printf("\nTX Diversity:\t\t\t\t[ ");
	diversity = (cfg->an_diversity >> 8) & 0xFF;
	if (diversity == AN_DIVERSITY_FACTORY_DEFAULT)
		printf("factory default");
	else if (diversity == AN_DIVERSITY_ANTENNA_1_ONLY)
		printf("antenna 1 only");
	else if (diversity == AN_DIVERSITY_ANTENNA_2_ONLY)
		printf("antenna 2 only");
	else if (diversity == AN_DIVERSITY_ANTENNA_1_AND_2)
		printf("antenna 1 and 2");
	printf(" ]");
	printf("\nTransmit power level:\t\t\t");
	an_printwords(&cfg->an_tx_power, 1);
	printf("\nRSS threshold:\t\t\t\t");
	an_printwords(&cfg->an_rss_thresh, 1);
	printf("\nNode name:\t\t\t\t");
	an_printstr((char *)&cfg->an_nodename, 16);
	printf("\nARL threshold:\t\t\t\t");
	an_printwords(&cfg->an_arl_thresh, 1);
	printf("\nARL decay:\t\t\t\t");
	an_printwords(&cfg->an_arl_decay, 1);
	printf("\nARL delay:\t\t\t\t");
	an_printwords(&cfg->an_arl_delay, 1);
	printf("\nConfiguration:\t\t\t\t[ ");
	if (cfg->an_home_product & AN_HOME_NETWORK)
		printf("Home Configuration");
	else
		printf("Enterprise Configuration");
	printf(" ]");

	printf("\n");
	printf("\n");
	an_readkeyinfo(iface);
}