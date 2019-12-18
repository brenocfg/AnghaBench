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
struct ath_rateioctl_rt {int* ratecode; } ;

/* Variables and functions */
 int IEEE80211_RATE_MCS ; 

__attribute__((used)) static inline int
dot11rate(struct ath_rateioctl_rt *rt, int rix)
{

	if (rt->ratecode[rix] & IEEE80211_RATE_MCS)
		return rt->ratecode[rix] & ~(IEEE80211_RATE_MCS);
	else
		return (rt->ratecode[rix] / 2);
}