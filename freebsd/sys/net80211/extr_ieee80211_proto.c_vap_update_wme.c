#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {int /*<<< orphan*/  (* iv_wme_update ) (struct ieee80211vap*,int /*<<< orphan*/ ) ;struct ieee80211com* iv_ic; } ;
struct TYPE_3__ {int /*<<< orphan*/  cap_wmeParams; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* wme_update ) (struct ieee80211com*) ;TYPE_1__ wme_chanParams; } ;
struct ieee80211com {TYPE_2__ ic_wme; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211com*) ; 

__attribute__((used)) static void
vap_update_wme(void *arg, int npending)
{
	struct ieee80211vap *vap = arg;
	struct ieee80211com *ic = vap->iv_ic;

	if (vap->iv_wme_update != NULL)
		vap->iv_wme_update(vap,
		    ic->ic_wme.wme_chanParams.cap_wmeParams);
	else
		ic->ic_wme.wme_update(ic);
}