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
struct wlan_mac_mac {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  mac_maclist; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int IFNAMSIZ ; 
 struct wlan_mac_mac* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct wlan_mac_mac* SLIST_NEXT (struct wlan_mac_mac*,int /*<<< orphan*/ ) ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_iface* wlan_first_interface () ; 
 struct wlan_mac_mac* wlan_mac_find_mac (struct wlan_iface*,char*) ; 
 scalar_t__ wlan_mac_index_decode (struct asn_oid const*,scalar_t__,char*,char*) ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 
 int /*<<< orphan*/  wm ; 

__attribute__((used)) static struct wlan_mac_mac *
wlan_get_next_acl_mac(const struct asn_oid *oid, uint sub,
    struct wlan_iface **wif)
{
	char wname[IFNAMSIZ];
	char mac[IEEE80211_ADDR_LEN];
	struct wlan_mac_mac *wmm;

	if (oid->len - sub == 0) {
		for (*wif = wlan_first_interface(); *wif != NULL;
		    *wif = wlan_next_interface(*wif)) {
			wmm = SLIST_FIRST(&(*wif)->mac_maclist);
			if (wmm != NULL)
				return (wmm);
		}
		return (NULL);
	}

	if (wlan_mac_index_decode(oid, sub, wname, mac) < 0 ||
	    (*wif = wlan_find_interface(wname)) == NULL ||
	    (wmm = wlan_mac_find_mac(*wif, mac)) == NULL)
		return (NULL);

	if ((wmm = SLIST_NEXT(wmm, wm)) != NULL)
		return (wmm);

	while ((*wif = wlan_next_interface(*wif)) != NULL)
		if ((wmm = SLIST_FIRST(&(*wif)->mac_maclist)) != NULL)
			break;

	return (wmm);
}