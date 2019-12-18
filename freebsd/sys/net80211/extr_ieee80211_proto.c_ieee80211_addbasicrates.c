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
struct ieee80211_rateset {int dummy; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 int /*<<< orphan*/  setbasicrates (struct ieee80211_rateset*,int,int) ; 

void
ieee80211_addbasicrates(struct ieee80211_rateset *rs,
    enum ieee80211_phymode mode)
{
	setbasicrates(rs, mode, 1);
}