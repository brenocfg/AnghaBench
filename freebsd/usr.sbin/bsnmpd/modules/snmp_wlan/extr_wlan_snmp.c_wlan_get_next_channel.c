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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint ;
struct wlan_iface {scalar_t__ status; scalar_t__ nchannels; struct ieee80211_channel* chanlist; } ;
struct ieee80211_channel {int dummy; } ;
struct asn_oid {scalar_t__ len; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 scalar_t__ RowStatus_active ; 
 scalar_t__ wlan_channel_index_decode (struct asn_oid const*,scalar_t__,char*,scalar_t__*) ; 
 struct wlan_iface* wlan_find_interface (char*) ; 
 struct wlan_iface* wlan_first_interface () ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 

__attribute__((used)) static struct ieee80211_channel *
wlan_get_next_channel(const struct asn_oid *oid, uint sub,
    struct wlan_iface **wif)
{
	uint32_t cindex;
	char wname[IFNAMSIZ];

	if (oid->len - sub == 0) {
		for (*wif = wlan_first_interface(); *wif != NULL;
		    *wif = wlan_next_interface(*wif)) {
			if ((*wif)->status != RowStatus_active)
				continue;
			if ((*wif)->nchannels != 0 && (*wif)->chanlist != NULL)
				return ((*wif)->chanlist);
		}
		return (NULL);
	}

	if (wlan_channel_index_decode(oid, sub, wname, &cindex) < 0)
		return (NULL);

	if ((*wif = wlan_find_interface(wname)) == NULL)
		return (NULL);

	if (cindex < (*wif)->nchannels)
		return ((*wif)->chanlist + cindex);

	while ((*wif = wlan_next_interface(*wif)) != NULL)
		if ((*wif)->status == RowStatus_active)
			if ((*wif)->nchannels != 0 && (*wif)->chanlist != NULL)
				return ((*wif)->chanlist);

	return (NULL);
}