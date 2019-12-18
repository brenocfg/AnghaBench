#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint ;
struct TYPE_2__ {struct ieee80211_roamparam* params; } ;
struct wlan_iface {scalar_t__ status; TYPE_1__ roamparams; } ;
struct ieee80211_roamparam {int dummy; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int IEEE80211_MODE_MAX ; 
 int IFNAMSIZ ; 
 scalar_t__ RowStatus_active ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_iface* wlan_first_interface () ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 
 scalar_t__ wlan_phy_index_decode (struct asn_oid const*,scalar_t__,char*,int*) ; 

__attribute__((used)) static struct ieee80211_roamparam *
wlan_get_next_roam_param(const struct asn_oid *oid, uint sub,
    struct wlan_iface **wif, uint32_t *phy)
{
	char wname[IFNAMSIZ];

	if (oid->len - sub == 0) {
		for (*wif = wlan_first_interface(); *wif != NULL;
		    *wif = wlan_next_interface(*wif)) {
			if ((*wif)->status != RowStatus_active)
				continue;
			*phy = 1;
			return ((*wif)->roamparams.params);
		}
		return (NULL);
	}

	if (wlan_phy_index_decode(oid, sub, wname, phy) < 0)
		return (NULL);

	if (*phy == 0  || (*wif = wlan_find_interface(wname)) == NULL)
		return (NULL);

	if (++(*phy) <= IEEE80211_MODE_MAX)
		return ((*wif)->roamparams.params + *phy - 1);

	*phy = 1;
	while ((*wif = wlan_next_interface(*wif)) != NULL)
		if ((*wif)->status == RowStatus_active)
			return ((*wif)->roamparams.params);

	return (NULL);
}