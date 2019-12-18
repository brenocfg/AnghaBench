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
struct ieee80211_node {int ni_txrate; } ;

/* Variables and functions */
 int nitems (int const*) ; 

__attribute__((used)) static __inline void
malo_updatetxrate(struct ieee80211_node *ni, int rix)
{
	static const int ieeerates[] =
	    { 2, 4, 11, 22, 44, 12, 18, 24, 36, 48, 96, 108 };
	if (rix < nitems(ieeerates))
		ni->ni_txrate = ieeerates[rix];
}