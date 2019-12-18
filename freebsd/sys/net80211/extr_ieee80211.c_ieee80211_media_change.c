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
typedef  scalar_t__ uint16_t ;
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ifmedia_entry {int dummy; } ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct ieee80211vap {scalar_t__ iv_des_mode; int /*<<< orphan*/  iv_flags; TYPE_1__ iv_media; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  media2mode (struct ifmedia_entry*,int /*<<< orphan*/ ,scalar_t__*) ; 

int
ieee80211_media_change(struct ifnet *ifp)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ifmedia_entry *ime = vap->iv_media.ifm_cur;
	uint16_t newmode;

	if (!media2mode(ime, vap->iv_flags, &newmode))
		return EINVAL;
	if (vap->iv_des_mode != newmode) {
		vap->iv_des_mode = newmode;
		/* XXX kick state machine if up+running */
	}
	return 0;
}