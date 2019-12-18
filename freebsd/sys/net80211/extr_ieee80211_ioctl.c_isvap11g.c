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
struct ieee80211vap {struct ieee80211_node* iv_bss; } ;
struct ieee80211_node {scalar_t__ ni_chan; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_CHAN_ANYC ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (scalar_t__) ; 

__attribute__((used)) static int
isvap11g(const struct ieee80211vap *vap)
{
	const struct ieee80211_node *bss = vap->iv_bss;
	return bss->ni_chan != IEEE80211_CHAN_ANYC &&
	    IEEE80211_IS_CHAN_ANYG(bss->ni_chan);
}