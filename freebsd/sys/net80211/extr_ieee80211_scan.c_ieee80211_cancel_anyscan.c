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
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {TYPE_1__* ic_scan_methods; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sc_cancel_anyscan ) (struct ieee80211vap*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ieee80211vap*) ; 

void
ieee80211_cancel_anyscan(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;

	ic->ic_scan_methods->sc_cancel_anyscan(vap);
}