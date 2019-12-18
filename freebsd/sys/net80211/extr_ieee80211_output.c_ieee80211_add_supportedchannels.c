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
struct ieee80211com {int /*<<< orphan*/  ic_chan_avail; } ;

/* Variables and functions */
 int IEEE80211_ELEMID_SUPPCHAN ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static uint8_t *
ieee80211_add_supportedchannels(uint8_t *frm, struct ieee80211com *ic)
{
	static const int ielen = 26;

	frm[0] = IEEE80211_ELEMID_SUPPCHAN;
	frm[1] = ielen;
	/* XXX not correct */
	memcpy(frm+2, ic->ic_chan_avail, ielen);
	return frm + 2 + ielen;
}