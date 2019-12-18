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
typedef  int /*<<< orphan*/  uint8_t ;
struct scanreq {int space; struct ieee80211req_scan_result* sr; } ;
struct ieee80211req_scan_result {int isr_len; int isr_ie_off; int isr_ie_len; int isr_nrates; int isr_ssid_len; int isr_meshid_len; int /*<<< orphan*/ * isr_rates; int /*<<< orphan*/  isr_bssid; int /*<<< orphan*/  isr_erp; int /*<<< orphan*/  isr_capinfo; int /*<<< orphan*/  isr_intval; int /*<<< orphan*/  isr_noise; int /*<<< orphan*/  isr_rssi; int /*<<< orphan*/  isr_flags; int /*<<< orphan*/  isr_freq; } ;
struct TYPE_4__ {int* data; } ;
struct ieee80211_scan_entry {int* se_ssid; int* se_rates; int* se_xrates; int* se_meshid; TYPE_2__ se_ies; int /*<<< orphan*/  se_bssid; int /*<<< orphan*/  se_erp; int /*<<< orphan*/  se_capinfo; int /*<<< orphan*/  se_intval; int /*<<< orphan*/  se_noise; int /*<<< orphan*/  se_rssi; TYPE_1__* se_chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  ic_flags; int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_RATE_MAXSIZE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int min (int,scalar_t__) ; 
 int scan_space (struct ieee80211_scan_entry const*,int*) ; 

__attribute__((used)) static void
get_scan_result(void *arg, const struct ieee80211_scan_entry *se)
{
	struct scanreq *req = arg;
	struct ieee80211req_scan_result *sr;
	int ielen, len, nr, nxr;
	uint8_t *cp;

	len = scan_space(se, &ielen);
	if (len > req->space)
		return;

	sr = req->sr;
	KASSERT(len <= 65535 && ielen <= 65535,
	    ("len %u ssid %u ie %u", len, se->se_ssid[1], ielen));
	sr->isr_len = len;
	sr->isr_ie_off = sizeof(struct ieee80211req_scan_result);
	sr->isr_ie_len = ielen;
	sr->isr_freq = se->se_chan->ic_freq;
	sr->isr_flags = se->se_chan->ic_flags;
	sr->isr_rssi = se->se_rssi;
	sr->isr_noise = se->se_noise;
	sr->isr_intval = se->se_intval;
	sr->isr_capinfo = se->se_capinfo;
	sr->isr_erp = se->se_erp;
	IEEE80211_ADDR_COPY(sr->isr_bssid, se->se_bssid);
	nr = min(se->se_rates[1], IEEE80211_RATE_MAXSIZE);
	memcpy(sr->isr_rates, se->se_rates+2, nr);
	nxr = min(se->se_xrates[1], IEEE80211_RATE_MAXSIZE - nr);
	memcpy(sr->isr_rates+nr, se->se_xrates+2, nxr);
	sr->isr_nrates = nr + nxr;

	/* copy SSID */
	sr->isr_ssid_len = se->se_ssid[1];
	cp = ((uint8_t *)sr) + sr->isr_ie_off;
	memcpy(cp, se->se_ssid+2, sr->isr_ssid_len);

	/* copy mesh id */
	cp += sr->isr_ssid_len;
	sr->isr_meshid_len = se->se_meshid[1];
	memcpy(cp, se->se_meshid+2, sr->isr_meshid_len);
	cp += sr->isr_meshid_len;

	if (ielen)
		memcpy(cp, se->se_ies.data, ielen);

	req->space -= len;
	req->sr = (struct ieee80211req_scan_result *)(((uint8_t *)sr) + len);
}