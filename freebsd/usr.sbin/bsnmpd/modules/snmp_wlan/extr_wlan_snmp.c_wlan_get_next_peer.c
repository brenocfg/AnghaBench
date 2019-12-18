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
typedef  scalar_t__ uint ;
struct wlan_peer {int dummy; } ;
struct wlan_iface {scalar_t__ mode; int /*<<< orphan*/  peerlist; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int IFNAMSIZ ; 
 struct wlan_peer* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct wlan_peer* SLIST_NEXT (struct wlan_peer*,int /*<<< orphan*/ ) ; 
 scalar_t__ WlanIfaceOperatingModeType_meshPoint ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_peer* wlan_find_peer (struct wlan_iface*,char*) ; 
 struct wlan_iface* wlan_first_interface () ; 
 scalar_t__ wlan_mac_index_decode (struct asn_oid const*,scalar_t__,char*,char*) ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 
 int /*<<< orphan*/  wp ; 

__attribute__((used)) static struct wlan_peer *
wlan_get_next_peer(const struct asn_oid *oid, uint sub, struct wlan_iface **wif)
{
	char wname[IFNAMSIZ];
	char pmac[IEEE80211_ADDR_LEN];
	struct wlan_peer *wip;

	if (oid->len - sub == 0) {
		for (*wif = wlan_first_interface(); *wif != NULL;
		    *wif = wlan_next_interface(*wif)) {
			if ((*wif)->mode ==
			    WlanIfaceOperatingModeType_meshPoint)
				continue;
			wip = SLIST_FIRST(&(*wif)->peerlist);
			if (wip != NULL)
				return (wip);
		}
		return (NULL);
	}

	if (wlan_mac_index_decode(oid, sub, wname, pmac) < 0 ||
	    (*wif = wlan_find_interface(wname)) == NULL ||
	    (wip = wlan_find_peer(*wif, pmac)) == NULL)
		return (NULL);

	if ((wip = SLIST_NEXT(wip, wp)) != NULL)
		return (wip);

	while ((*wif = wlan_next_interface(*wif)) != NULL) {
		if ((*wif)->mode == WlanIfaceOperatingModeType_meshPoint)
			continue;
		if ((wip = SLIST_FIRST(&(*wif)->peerlist)) != NULL)
			break;
	}

	return (wip);
}