#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* info; } ;
struct TYPE_4__ {scalar_t__ phy; int dot11Rate; } ;
typedef  TYPE_2__ HAL_RATE_TABLE ;

/* Variables and functions */
 int IEEE80211_RATE_VAL ; 
 scalar_t__ IEEE80211_T_HT ; 

__attribute__((used)) static int
dot11rate(const HAL_RATE_TABLE *rt, int rix)
{
	if (rix < 0)
		return -1;
	return rt->info[rix].phy == IEEE80211_T_HT ?
	    rt->info[rix].dot11Rate : (rt->info[rix].dot11Rate & IEEE80211_RATE_VAL) / 2;
}