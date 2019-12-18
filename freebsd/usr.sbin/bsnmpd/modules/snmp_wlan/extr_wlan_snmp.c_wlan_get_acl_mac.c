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
typedef  int /*<<< orphan*/  uint ;
struct wlan_mac_mac {int dummy; } ;
struct wlan_iface {int dummy; } ;
struct asn_oid {int dummy; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int IFNAMSIZ ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_mac_mac* wlan_mac_find_mac (struct wlan_iface*,char*) ; 
 scalar_t__ wlan_mac_index_decode (struct asn_oid const*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static struct wlan_mac_mac *
wlan_get_acl_mac(const struct asn_oid *oid, uint sub, struct wlan_iface **wif)
{
	char wname[IFNAMSIZ];
	char mac[IEEE80211_ADDR_LEN];

	if (wlan_mac_index_decode(oid, sub, wname, mac) < 0)
		return (NULL);

	if ((*wif = wlan_find_interface(wname)) == NULL)
		return (NULL);

	return (wlan_mac_find_mac(*wif, mac));
}