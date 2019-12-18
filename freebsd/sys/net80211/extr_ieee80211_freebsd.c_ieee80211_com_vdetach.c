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
struct ieee80211vap {int /*<<< orphan*/  iv_com_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_COM_DETACHED ; 
 int /*<<< orphan*/  IEEE80211_COM_REF ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_load_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int msecs_to_ticks (int) ; 
 int /*<<< orphan*/  pause (char*,int) ; 

void
ieee80211_com_vdetach(struct ieee80211vap *vap)
{
	int sleep_time;

	sleep_time = msecs_to_ticks(250);
	atomic_set_32(&vap->iv_com_state, IEEE80211_COM_DETACHED);
	while (MS(atomic_load_32(&vap->iv_com_state), IEEE80211_COM_REF) != 0)
		pause("comref", sleep_time);
}