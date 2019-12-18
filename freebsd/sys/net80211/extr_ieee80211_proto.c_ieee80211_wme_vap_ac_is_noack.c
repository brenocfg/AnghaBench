#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {TYPE_4__* iv_ic; } ;
struct TYPE_6__ {TYPE_1__* cap_wmeParams; } ;
struct TYPE_7__ {TYPE_2__ wme_chanParams; } ;
struct TYPE_8__ {TYPE_3__ ic_wme; } ;
struct TYPE_5__ {int /*<<< orphan*/  wmep_noackPolicy; } ;

/* Variables and functions */
 int WME_NUM_AC ; 

int
ieee80211_wme_vap_ac_is_noack(struct ieee80211vap *vap, int ac)
{
	/* Bounds/sanity check */
	if (ac < 0 || ac >= WME_NUM_AC)
		return (0);

	/* Again, there's only one global context for now */
	return (!! vap->iv_ic->ic_wme.wme_chanParams.cap_wmeParams[ac].wmep_noackPolicy);
}