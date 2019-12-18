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
struct wpa_scan_res {int caps; int flags; int snr; int level; scalar_t__ est_throughput; int qual; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREAT_SNR ; 
 int IEEE80211_CAP_PRIVACY ; 
 int IS_5GHZ (int /*<<< orphan*/ ) ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_RSN ; 
 int /*<<< orphan*/  WPA_IE_VENDOR_TYPE ; 
 int WPA_SCAN_LEVEL_DBM ; 
 int abs (int) ; 
 int /*<<< orphan*/ * wpa_scan_get_ie (struct wpa_scan_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpa_scan_get_vendor_ie (struct wpa_scan_res*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_scan_result_compar(const void *a, const void *b)
{
#define MIN(a,b) a < b ? a : b
	struct wpa_scan_res **_wa = (void *) a;
	struct wpa_scan_res **_wb = (void *) b;
	struct wpa_scan_res *wa = *_wa;
	struct wpa_scan_res *wb = *_wb;
	int wpa_a, wpa_b;
	int snr_a, snr_b, snr_a_full, snr_b_full;

	/* WPA/WPA2 support preferred */
	wpa_a = wpa_scan_get_vendor_ie(wa, WPA_IE_VENDOR_TYPE) != NULL ||
		wpa_scan_get_ie(wa, WLAN_EID_RSN) != NULL;
	wpa_b = wpa_scan_get_vendor_ie(wb, WPA_IE_VENDOR_TYPE) != NULL ||
		wpa_scan_get_ie(wb, WLAN_EID_RSN) != NULL;

	if (wpa_b && !wpa_a)
		return 1;
	if (!wpa_b && wpa_a)
		return -1;

	/* privacy support preferred */
	if ((wa->caps & IEEE80211_CAP_PRIVACY) == 0 &&
	    (wb->caps & IEEE80211_CAP_PRIVACY))
		return 1;
	if ((wa->caps & IEEE80211_CAP_PRIVACY) &&
	    (wb->caps & IEEE80211_CAP_PRIVACY) == 0)
		return -1;

	if (wa->flags & wb->flags & WPA_SCAN_LEVEL_DBM) {
		snr_a_full = wa->snr;
		snr_a = MIN(wa->snr, GREAT_SNR);
		snr_b_full = wb->snr;
		snr_b = MIN(wb->snr, GREAT_SNR);
	} else {
		/* Level is not in dBm, so we can't calculate
		 * SNR. Just use raw level (units unknown). */
		snr_a = snr_a_full = wa->level;
		snr_b = snr_b_full = wb->level;
	}

	/* if SNR is close, decide by max rate or frequency band */
	if (snr_a && snr_b && abs(snr_b - snr_a) < 7) {
		if (wa->est_throughput != wb->est_throughput)
			return (int) wb->est_throughput -
				(int) wa->est_throughput;
	}
	if ((snr_a && snr_b && abs(snr_b - snr_a) < 5) ||
	    (wa->qual && wb->qual && abs(wb->qual - wa->qual) < 10)) {
		if (IS_5GHZ(wa->freq) ^ IS_5GHZ(wb->freq))
			return IS_5GHZ(wa->freq) ? -1 : 1;
	}

	/* all things being equal, use SNR; if SNRs are
	 * identical, use quality values since some drivers may only report
	 * that value and leave the signal level zero */
	if (snr_b_full == snr_a_full)
		return wb->qual - wa->qual;
	return snr_b_full - snr_a_full;
#undef MIN
}