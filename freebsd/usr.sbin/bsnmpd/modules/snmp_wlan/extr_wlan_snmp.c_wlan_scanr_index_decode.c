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
typedef  char uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct asn_oid {size_t* subs; } ;

/* Variables and functions */
 size_t IEEE80211_ADDR_LEN ; 
 size_t IEEE80211_NWID_LEN ; 
 size_t IFNAMSIZ ; 

__attribute__((used)) static int
wlan_scanr_index_decode(const struct asn_oid *oid, uint sub,
    char *wname, uint8_t *ssid, uint8_t *bssid)
{
	uint32_t i;
	int offset;

	if (oid->subs[sub] >= IFNAMSIZ)
		return (-1);
	for (i = 0; i < oid->subs[sub]; i++)
		wname[i] = oid->subs[sub + i + 1];
	wname[oid->subs[sub]] = '\0';

	offset = sub + oid->subs[sub] + 1;
	if (oid->subs[offset] > IEEE80211_NWID_LEN)
		return (-1);
	for (i = 0; i < oid->subs[offset]; i++)
		ssid[i] = oid->subs[offset + i + 1];
	ssid[i] = '\0';

	offset = sub + oid->subs[sub] + oid->subs[offset] + 2;
	if (oid->subs[offset] != IEEE80211_ADDR_LEN)
		return (-1);
	for (i = 0; i < IEEE80211_ADDR_LEN; i++)
		bssid[i] = oid->subs[offset + i + 1];

	return (0);
}