#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {unsigned int max_sched_scan_ssids; int pno; int pno_sched_pending; scalar_t__ wpa_state; size_t max_match_sets; int sched_scan_plans_num; int mac_addr_rand_enable; scalar_t__ mac_addr_pno; int /*<<< orphan*/ * manual_sched_scan_freqs; TYPE_2__* conf; struct sched_scan_plan* sched_scan_plans; scalar_t__ sched_scan_stop_req; scalar_t__ sched_scanning; int /*<<< orphan*/  sched_scan_supported; } ;
struct wpa_ssid {struct wpa_ssid* pnext; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; scalar_t__ scan_ssid; struct wpa_ssid* next; } ;
struct wpa_driver_scan_params {size_t num_ssids; int sched_scan_plans_num; int mac_addr_rand; TYPE_3__* filter_ssids; scalar_t__ mac_addr_mask; scalar_t__ mac_addr; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  sched_scan_start_delay; struct sched_scan_plan* sched_scan_plans; scalar_t__ filter_rssi; int /*<<< orphan*/  num_filter_ssids; TYPE_1__* ssids; } ;
struct wpa_driver_scan_filter {int dummy; } ;
struct sched_scan_plan {int interval; scalar_t__ iterations; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_7__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_6__ {int num_prio; int sched_scan_interval; int /*<<< orphan*/  sched_scan_start_delay; scalar_t__ filter_rssi; struct wpa_ssid** pssid; struct wpa_ssid* ssid; } ;
struct TYPE_5__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ ETH_ALEN ; 
 int MAC_ADDR_RAND_PNO ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 unsigned int WPAS_MAX_SCAN_SSIDS ; 
 scalar_t__ WPA_COMPLETED ; 
 scalar_t__ WPA_SCANNING ; 
 TYPE_3__* os_calloc (size_t,int) ; 
 int /*<<< orphan*/  os_free (TYPE_3__*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_scan_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_scan_set_relative_rssi_params (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_scan (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 
 int wpa_supplicant_start_sched_scan (struct wpa_supplicant*,struct wpa_driver_scan_params*) ; 
 int /*<<< orphan*/  wpas_network_disabled (struct wpa_supplicant*,struct wpa_ssid*) ; 

int wpas_start_pno(struct wpa_supplicant *wpa_s)
{
	int ret, prio;
	size_t i, num_ssid, num_match_ssid;
	struct wpa_ssid *ssid;
	struct wpa_driver_scan_params params;
	struct sched_scan_plan scan_plan;
	unsigned int max_sched_scan_ssids;

	if (!wpa_s->sched_scan_supported)
		return -1;

	if (wpa_s->max_sched_scan_ssids > WPAS_MAX_SCAN_SSIDS)
		max_sched_scan_ssids = WPAS_MAX_SCAN_SSIDS;
	else
		max_sched_scan_ssids = wpa_s->max_sched_scan_ssids;
	if (max_sched_scan_ssids < 1)
		return -1;

	if (wpa_s->pno || wpa_s->pno_sched_pending)
		return 0;

	if ((wpa_s->wpa_state > WPA_SCANNING) &&
	    (wpa_s->wpa_state < WPA_COMPLETED)) {
		wpa_printf(MSG_ERROR, "PNO: In assoc process");
		return -EAGAIN;
	}

	if (wpa_s->wpa_state == WPA_SCANNING) {
		wpa_supplicant_cancel_scan(wpa_s);
		if (wpa_s->sched_scanning) {
			wpa_printf(MSG_DEBUG, "Schedule PNO on completion of "
				   "ongoing sched scan");
			wpa_supplicant_cancel_sched_scan(wpa_s);
			wpa_s->pno_sched_pending = 1;
			return 0;
		}
	}

	if (wpa_s->sched_scan_stop_req) {
		wpa_printf(MSG_DEBUG,
			   "Schedule PNO after previous sched scan has stopped");
		wpa_s->pno_sched_pending = 1;
		return 0;
	}

	os_memset(&params, 0, sizeof(params));

	num_ssid = num_match_ssid = 0;
	ssid = wpa_s->conf->ssid;
	while (ssid) {
		if (!wpas_network_disabled(wpa_s, ssid)) {
			num_match_ssid++;
			if (ssid->scan_ssid)
				num_ssid++;
		}
		ssid = ssid->next;
	}

	if (num_match_ssid == 0) {
		wpa_printf(MSG_DEBUG, "PNO: No configured SSIDs");
		return -1;
	}

	if (num_match_ssid > num_ssid) {
		params.num_ssids++; /* wildcard */
		num_ssid++;
	}

	if (num_ssid > max_sched_scan_ssids) {
		wpa_printf(MSG_DEBUG, "PNO: Use only the first %u SSIDs from "
			   "%u", max_sched_scan_ssids, (unsigned int) num_ssid);
		num_ssid = max_sched_scan_ssids;
	}

	if (num_match_ssid > wpa_s->max_match_sets) {
		num_match_ssid = wpa_s->max_match_sets;
		wpa_dbg(wpa_s, MSG_DEBUG, "PNO: Too many SSIDs to match");
	}
	params.filter_ssids = os_calloc(num_match_ssid,
					sizeof(struct wpa_driver_scan_filter));
	if (params.filter_ssids == NULL)
		return -1;

	i = 0;
	prio = 0;
	ssid = wpa_s->conf->pssid[prio];
	while (ssid) {
		if (!wpas_network_disabled(wpa_s, ssid)) {
			if (ssid->scan_ssid && params.num_ssids < num_ssid) {
				params.ssids[params.num_ssids].ssid =
					ssid->ssid;
				params.ssids[params.num_ssids].ssid_len =
					 ssid->ssid_len;
				params.num_ssids++;
			}
			os_memcpy(params.filter_ssids[i].ssid, ssid->ssid,
				  ssid->ssid_len);
			params.filter_ssids[i].ssid_len = ssid->ssid_len;
			params.num_filter_ssids++;
			i++;
			if (i == num_match_ssid)
				break;
		}
		if (ssid->pnext)
			ssid = ssid->pnext;
		else if (prio + 1 == wpa_s->conf->num_prio)
			break;
		else
			ssid = wpa_s->conf->pssid[++prio];
	}

	if (wpa_s->conf->filter_rssi)
		params.filter_rssi = wpa_s->conf->filter_rssi;

	if (wpa_s->sched_scan_plans_num) {
		params.sched_scan_plans = wpa_s->sched_scan_plans;
		params.sched_scan_plans_num = wpa_s->sched_scan_plans_num;
	} else {
		/* Set one scan plan that will run infinitely */
		if (wpa_s->conf->sched_scan_interval)
			scan_plan.interval = wpa_s->conf->sched_scan_interval;
		else
			scan_plan.interval = 10;

		scan_plan.iterations = 0;
		params.sched_scan_plans = &scan_plan;
		params.sched_scan_plans_num = 1;
	}

	params.sched_scan_start_delay = wpa_s->conf->sched_scan_start_delay;

	if (params.freqs == NULL && wpa_s->manual_sched_scan_freqs) {
		wpa_dbg(wpa_s, MSG_DEBUG, "Limit sched scan to specified channels");
		params.freqs = wpa_s->manual_sched_scan_freqs;
	}

	if ((wpa_s->mac_addr_rand_enable & MAC_ADDR_RAND_PNO) &&
	    wpa_s->wpa_state <= WPA_SCANNING) {
		params.mac_addr_rand = 1;
		if (wpa_s->mac_addr_pno) {
			params.mac_addr = wpa_s->mac_addr_pno;
			params.mac_addr_mask = wpa_s->mac_addr_pno + ETH_ALEN;
		}
	}

	wpa_scan_set_relative_rssi_params(wpa_s, &params);

	ret = wpa_supplicant_start_sched_scan(wpa_s, &params);
	os_free(params.filter_ssids);
	if (ret == 0)
		wpa_s->pno = 1;
	else
		wpa_msg(wpa_s, MSG_ERROR, "Failed to schedule PNO");
	return ret;
}