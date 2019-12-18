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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint ;
struct asn_oid {size_t len; int* subs; } ;

/* Variables and functions */
 size_t IEEE80211_ADDR_LEN ; 
 int IFNAMSIZ ; 

__attribute__((used)) static int
wlan_mac_index_decode(const struct asn_oid *oid, uint sub,
    char *wname, uint8_t *mac)
{
	uint32_t i;
	int mac_off;

	if (oid->len - sub != oid->subs[sub] + 2 + IEEE80211_ADDR_LEN
	    || oid->subs[sub] >= IFNAMSIZ)
		return (-1);

	for (i = 0; i < oid->subs[sub]; i++)
		wname[i] = oid->subs[sub + i + 1];
	wname[i] = '\0';

	mac_off = sub + oid->subs[sub] + 1;
	if (oid->subs[mac_off] != IEEE80211_ADDR_LEN)
		return (-1);
	for (i = 0; i < IEEE80211_ADDR_LEN; i++)
		mac[i] = oid->subs[mac_off + i + 1];

	return (0);
}