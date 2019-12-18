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
struct ifmediareq {int ifm_status; int /*<<< orphan*/  ifm_active; } ;

/* Variables and functions */
 int IFM_ACTIVE ; 
#define  IFM_ATM 130 
#define  IFM_ETHER 129 
#define  IFM_IEEE80211 128 
 int /*<<< orphan*/  IFM_IEEE80211_STA ; 
 int /*<<< orphan*/  IFM_OPMODE (int /*<<< orphan*/ ) ; 
 int IFM_TYPE (int /*<<< orphan*/ ) ; 

const char *
ifconfig_media_get_status(const struct ifmediareq *ifmr)
{
	switch (IFM_TYPE(ifmr->ifm_active)) {
	case IFM_ETHER:
	case IFM_ATM:
		if (ifmr->ifm_status & IFM_ACTIVE) {
			return ("active");
		} else {
			return ("no carrier");
		}
		break;

	case IFM_IEEE80211:
		if (ifmr->ifm_status & IFM_ACTIVE) {
			/* NB: only sta mode associates */
			if (IFM_OPMODE(ifmr->ifm_active) == IFM_IEEE80211_STA) {
				return ("associated");
			} else {
				return ("running");
			}
		} else {
			return ("no carrier");
		}
		break;
	default:
		return ("");
	}
}