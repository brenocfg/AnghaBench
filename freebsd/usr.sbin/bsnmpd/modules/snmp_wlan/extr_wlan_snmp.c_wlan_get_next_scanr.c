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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint ;
struct wlan_scan_result {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  scanlist; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_NWID_LEN ; 
 int IFNAMSIZ ; 
 struct wlan_scan_result* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct wlan_scan_result* SLIST_NEXT (struct wlan_scan_result*,int /*<<< orphan*/ ) ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_iface* wlan_first_interface () ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 
 struct wlan_scan_result* wlan_scan_find_result (struct wlan_iface*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wlan_scanr_index_decode (struct asn_oid const*,scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsr ; 

__attribute__((used)) static struct wlan_scan_result *
wlan_get_next_scanr(const struct asn_oid *oid, uint sub,
    struct wlan_iface **wif)
{
	char wname[IFNAMSIZ];
	uint8_t ssid[IEEE80211_NWID_LEN + 1];
	uint8_t bssid[IEEE80211_ADDR_LEN];
	struct wlan_scan_result *sr;

	if (oid->len - sub == 0) {
		for (*wif = wlan_first_interface(); *wif != NULL;
		    *wif = wlan_next_interface(*wif)) {
			sr = SLIST_FIRST(&(*wif)->scanlist);
			if (sr != NULL)
				return (sr);
		}
		return (NULL);
	}

	if (wlan_scanr_index_decode(oid, sub, wname, ssid, bssid) < 0 ||
	    (*wif = wlan_find_interface(wname)) == NULL ||
	    (sr = wlan_scan_find_result(*wif, ssid, bssid)) == NULL)
		return (NULL);

	if ((sr = SLIST_NEXT(sr, wsr)) != NULL)
		return (sr);

	while ((*wif = wlan_next_interface(*wif)) != NULL)
		if ((sr = SLIST_FIRST(&(*wif)->scanlist)) != NULL)
			break;

	return (sr);
}