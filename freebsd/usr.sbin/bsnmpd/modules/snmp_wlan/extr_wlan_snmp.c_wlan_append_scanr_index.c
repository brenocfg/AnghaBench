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
struct asn_oid {size_t len; int* subs; } ;

/* Variables and functions */
 size_t IEEE80211_ADDR_LEN ; 
 int strlen (char*) ; 

__attribute__((used)) static void
wlan_append_scanr_index(struct asn_oid *oid, uint sub, char *wname,
    uint8_t *ssid, uint8_t *bssid)
{
	uint32_t i;

	oid->len = sub + strlen(wname) + strlen(ssid) + IEEE80211_ADDR_LEN + 3;
	oid->subs[sub] = strlen(wname);
	for (i = 1; i <= strlen(wname); i++)
		oid->subs[sub + i] = wname[i - 1];

	sub += strlen(wname) + 1;
	oid->subs[sub] = strlen(ssid);
	for (i = 1; i <= strlen(ssid); i++)
		oid->subs[sub + i] = ssid[i - 1];

	sub += strlen(ssid) + 1;
	oid->subs[sub] = IEEE80211_ADDR_LEN;
	for (i = 1; i <= IEEE80211_ADDR_LEN; i++)
		oid->subs[sub + i] = bssid[i - 1];
}