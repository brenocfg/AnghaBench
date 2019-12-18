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
typedef  int uint32_t ;
struct ieee80211vap {int /*<<< orphan*/  iv_com_state; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int EOVERFLOW ; 
 int IEEE80211_COM_DETACHED ; 
 int /*<<< orphan*/  IEEE80211_COM_REF ; 
 int /*<<< orphan*/  IEEE80211_COM_REF_ADD ; 
 scalar_t__ IEEE80211_COM_REF_MAX ; 
 scalar_t__ MS (int,int /*<<< orphan*/ ) ; 
 int atomic_fetchadd_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_subtract_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ieee80211_com_vincref(struct ieee80211vap *vap)
{
	uint32_t ostate;

	ostate = atomic_fetchadd_32(&vap->iv_com_state, IEEE80211_COM_REF_ADD);

	if (ostate & IEEE80211_COM_DETACHED) {
		atomic_subtract_32(&vap->iv_com_state, IEEE80211_COM_REF_ADD);
		return (ENETDOWN);
	}

	if (MS(ostate, IEEE80211_COM_REF) == IEEE80211_COM_REF_MAX) {
		atomic_subtract_32(&vap->iv_com_state, IEEE80211_COM_REF_ADD);
		return (EOVERFLOW);
	}

	return (0);
}