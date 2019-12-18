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
typedef  int uint8_t ;
struct ieee80211_channel {int ic_minpower; int ic_maxpower; } ;

/* Variables and functions */
 int IEEE80211_ELEMID_PWRCAP ; 

__attribute__((used)) static uint8_t *
ieee80211_add_powercapability(uint8_t *frm, const struct ieee80211_channel *c)
{
	frm[0] = IEEE80211_ELEMID_PWRCAP;
	frm[1] = 2;
	frm[2] = c->ic_minpower;
	frm[3] = c->ic_maxpower;
	return frm + 4;
}