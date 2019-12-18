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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int* next_scan_freqs; scalar_t__ normal_scans; scalar_t__ current_ssid; scalar_t__ extra_blacklist_count; scalar_t__ current_bss; scalar_t__ disconnected; scalar_t__ own_disconnect_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int* get_bss_freqs_in_ess (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int wpa_blacklist_add (struct wpa_supplicant*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_req_scan (struct wpa_supplicant*,int,int) ; 
 int /*<<< orphan*/  wpa_supplicant_timeout ; 
 int /*<<< orphan*/  wpas_auth_failed (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  wpas_connect_work_done (struct wpa_supplicant*) ; 

void wpas_connection_failed(struct wpa_supplicant *wpa_s, const u8 *bssid)
{
	int timeout;
	int count;
	int *freqs = NULL;

	wpas_connect_work_done(wpa_s);

	/*
	 * Remove possible authentication timeout since the connection failed.
	 */
	eloop_cancel_timeout(wpa_supplicant_timeout, wpa_s, NULL);

	/*
	 * There is no point in blacklisting the AP if this event is
	 * generated based on local request to disconnect.
	 */
	if (wpa_s->own_disconnect_req) {
		wpa_s->own_disconnect_req = 0;
		wpa_dbg(wpa_s, MSG_DEBUG,
			"Ignore connection failure due to local request to disconnect");
		return;
	}
	if (wpa_s->disconnected) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Ignore connection failure "
			"indication since interface has been put into "
			"disconnected state");
		return;
	}

	/*
	 * Add the failed BSSID into the blacklist and speed up next scan
	 * attempt if there could be other APs that could accept association.
	 * The current blacklist count indicates how many times we have tried
	 * connecting to this AP and multiple attempts mean that other APs are
	 * either not available or has already been tried, so that we can start
	 * increasing the delay here to avoid constant scanning.
	 */
	count = wpa_blacklist_add(wpa_s, bssid);
	if (count == 1 && wpa_s->current_bss) {
		/*
		 * This BSS was not in the blacklist before. If there is
		 * another BSS available for the same ESS, we should try that
		 * next. Otherwise, we may as well try this one once more
		 * before allowing other, likely worse, ESSes to be considered.
		 */
		freqs = get_bss_freqs_in_ess(wpa_s);
		if (freqs) {
			wpa_dbg(wpa_s, MSG_DEBUG, "Another BSS in this ESS "
				"has been seen; try it next");
			wpa_blacklist_add(wpa_s, bssid);
			/*
			 * On the next scan, go through only the known channels
			 * used in this ESS based on previous scans to speed up
			 * common load balancing use case.
			 */
			os_free(wpa_s->next_scan_freqs);
			wpa_s->next_scan_freqs = freqs;
		}
	}

	/*
	 * Add previous failure count in case the temporary blacklist was
	 * cleared due to no other BSSes being available.
	 */
	count += wpa_s->extra_blacklist_count;

	if (count > 3 && wpa_s->current_ssid) {
		wpa_printf(MSG_DEBUG, "Continuous association failures - "
			   "consider temporary network disabling");
		wpas_auth_failed(wpa_s, "CONN_FAILED");
	}

	switch (count) {
	case 1:
		timeout = 100;
		break;
	case 2:
		timeout = 500;
		break;
	case 3:
		timeout = 1000;
		break;
	case 4:
		timeout = 5000;
		break;
	default:
		timeout = 10000;
		break;
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "Blacklist count %d --> request scan in %d "
		"ms", count, timeout);

	/*
	 * TODO: if more than one possible AP is available in scan results,
	 * could try the other ones before requesting a new scan.
	 */

	/* speed up the connection attempt with normal scan */
	wpa_s->normal_scans = 0;
	wpa_supplicant_req_scan(wpa_s, timeout / 1000,
				1000 * (timeout % 1000));
}