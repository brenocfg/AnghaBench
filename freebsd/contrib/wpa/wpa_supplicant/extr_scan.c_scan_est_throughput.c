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
typedef  int u8 ;
struct wpa_supplicant {int hw_capab; } ;
struct wpa_scan_res {int snr; int est_throughput; } ;
typedef  enum local_hw_capab { ____Placeholder_local_hw_capab } local_hw_capab ;

/* Variables and functions */
 int CAPAB_HT ; 
 int CAPAB_HT40 ; 
 int CAPAB_VHT ; 
 int const HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK ; 
 int const VHT_OPMODE_CHANNEL_WIDTH_MASK ; 
 int /*<<< orphan*/  WLAN_EID_HT_CAP ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int /*<<< orphan*/  WLAN_EID_VHT_CAP ; 
 int /*<<< orphan*/  WLAN_EID_VHT_OPERATION ; 
 int max_ht20_rate (int) ; 
 int max_ht40_rate (int) ; 
 int max_vht80_rate (int) ; 
 int* wpa_scan_get_ie (struct wpa_scan_res*,int /*<<< orphan*/ ) ; 
 int wpa_scan_get_max_rate (struct wpa_scan_res*) ; 

void scan_est_throughput(struct wpa_supplicant *wpa_s,
			 struct wpa_scan_res *res)
{
	enum local_hw_capab capab = wpa_s->hw_capab;
	int rate; /* max legacy rate in 500 kb/s units */
	const u8 *ie;
	unsigned int est, tmp;
	int snr = res->snr;

	if (res->est_throughput)
		return;

	/* Get maximum legacy rate */
	rate = wpa_scan_get_max_rate(res);

	/* Limit based on estimated SNR */
	if (rate > 1 * 2 && snr < 1)
		rate = 1 * 2;
	else if (rate > 2 * 2 && snr < 4)
		rate = 2 * 2;
	else if (rate > 6 * 2 && snr < 5)
		rate = 6 * 2;
	else if (rate > 9 * 2 && snr < 6)
		rate = 9 * 2;
	else if (rate > 12 * 2 && snr < 7)
		rate = 12 * 2;
	else if (rate > 18 * 2 && snr < 10)
		rate = 18 * 2;
	else if (rate > 24 * 2 && snr < 11)
		rate = 24 * 2;
	else if (rate > 36 * 2 && snr < 15)
		rate = 36 * 2;
	else if (rate > 48 * 2 && snr < 19)
		rate = 48 * 2;
	else if (rate > 54 * 2 && snr < 21)
		rate = 54 * 2;
	est = rate * 500;

	if (capab == CAPAB_HT || capab == CAPAB_HT40 || capab == CAPAB_VHT) {
		ie = wpa_scan_get_ie(res, WLAN_EID_HT_CAP);
		if (ie) {
			tmp = max_ht20_rate(snr);
			if (tmp > est)
				est = tmp;
		}
	}

	if (capab == CAPAB_HT40 || capab == CAPAB_VHT) {
		ie = wpa_scan_get_ie(res, WLAN_EID_HT_OPERATION);
		if (ie && ie[1] >= 2 &&
		    (ie[3] & HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK)) {
			tmp = max_ht40_rate(snr);
			if (tmp > est)
				est = tmp;
		}
	}

	if (capab == CAPAB_VHT) {
		/* Use +1 to assume VHT is always faster than HT */
		ie = wpa_scan_get_ie(res, WLAN_EID_VHT_CAP);
		if (ie) {
			tmp = max_ht20_rate(snr) + 1;
			if (tmp > est)
				est = tmp;

			ie = wpa_scan_get_ie(res, WLAN_EID_HT_OPERATION);
			if (ie && ie[1] >= 2 &&
			    (ie[3] &
			     HT_INFO_HT_PARAM_SECONDARY_CHNL_OFF_MASK)) {
				tmp = max_ht40_rate(snr) + 1;
				if (tmp > est)
					est = tmp;
			}

			ie = wpa_scan_get_ie(res, WLAN_EID_VHT_OPERATION);
			if (ie && ie[1] >= 1 &&
			    (ie[2] & VHT_OPMODE_CHANNEL_WIDTH_MASK)) {
				tmp = max_vht80_rate(snr) + 1;
				if (tmp > est)
					est = tmp;
			}
		}
	}

	/* TODO: channel utilization and AP load (e.g., from AP Beacon) */

	res->est_throughput = est;
}