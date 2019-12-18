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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211req_scan_result {int dummy; } ;
struct TYPE_2__ {int len; } ;
struct ieee80211_scan_entry {int* se_ssid; int* se_meshid; TYPE_1__ se_ies; } ;

/* Variables and functions */
 size_t roundup (size_t,int) ; 

__attribute__((used)) static size_t
scan_space(const struct ieee80211_scan_entry *se, int *ielen)
{
	size_t len;

	*ielen = se->se_ies.len;
	/*
	 * NB: ie's can be no more than 255 bytes and the max 802.11
	 * packet is <3Kbytes so we are sure this doesn't overflow
	 * 16-bits; if this is a concern we can drop the ie's.
	 */
	len = sizeof(struct ieee80211req_scan_result) + se->se_ssid[1] +
	    se->se_meshid[1] + *ielen;
	return roundup(len, sizeof(uint32_t));
}