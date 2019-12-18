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
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel const*) ; 
 int IWI_CHAN_2GHZ ; 
 int IWI_CHAN_5GHZ ; 

__attribute__((used)) static __inline int
scan_band(const struct ieee80211_channel *c)
{
	return IEEE80211_IS_CHAN_5GHZ(c) ?  IWI_CHAN_5GHZ : IWI_CHAN_2GHZ;
}