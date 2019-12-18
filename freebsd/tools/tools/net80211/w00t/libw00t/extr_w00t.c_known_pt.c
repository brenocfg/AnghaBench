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
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int is_arp (struct ieee80211_frame*,int) ; 

char *known_pt(struct ieee80211_frame *wh, int *len)
{
	static char *known_pt_arp = "\xAA\xAA\x03\x00\x00\x00\x08\x06";
	static char *known_pt_ip = "\xAA\xAA\x03\x00\x00\x00\x08\x00";
	int arp;

	arp = is_arp(wh, *len);
	*len = 8;
	if (arp)
		return known_pt_arp;
	else
		return known_pt_ip;
}