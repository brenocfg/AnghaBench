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
struct ieee80211vap {TYPE_1__* iv_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_destroyif (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wlan_cloner ; 

void
ieee80211_vap_destroy(struct ieee80211vap *vap)
{
	CURVNET_SET(vap->iv_ifp->if_vnet);
	if_clone_destroyif(wlan_cloner, vap->iv_ifp);
	CURVNET_RESTORE();
}