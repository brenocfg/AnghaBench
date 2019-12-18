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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211vap {int /*<<< orphan*/  iv_com_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_COM_REF ; 
 int /*<<< orphan*/  IEEE80211_COM_REF_ADD ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fetchadd_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ieee80211_com_vdecref(struct ieee80211vap *vap)
{
	uint32_t ostate;

	ostate = atomic_fetchadd_32(&vap->iv_com_state, -IEEE80211_COM_REF_ADD);

	KASSERT(MS(ostate, IEEE80211_COM_REF) != 0,
	    ("com reference counter underflow"));

	(void) ostate;
}