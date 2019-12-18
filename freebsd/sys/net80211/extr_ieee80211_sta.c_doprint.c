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
struct ieee80211vap {TYPE_1__* iv_ic; } ;
struct TYPE_2__ {int ic_flags; } ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_BEACON 129 
#define  IEEE80211_FC0_SUBTYPE_PROBE_REQ 128 
 int IEEE80211_F_SCAN ; 

__attribute__((used)) static __inline int
doprint(struct ieee80211vap *vap, int subtype)
{
	switch (subtype) {
	case IEEE80211_FC0_SUBTYPE_BEACON:
		return (vap->iv_ic->ic_flags & IEEE80211_F_SCAN);
	case IEEE80211_FC0_SUBTYPE_PROBE_REQ:
		return 0;
	}
	return 1;
}