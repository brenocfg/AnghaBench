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
struct ieee80211vap {scalar_t__ iv_opmode; int /*<<< orphan*/ * iv_bss; TYPE_1__* iv_ic; } ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ic_node_getsignal ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  ieee80211_getrssi (struct ieee80211vap*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ieee80211_getsignal(struct ieee80211vap *vap, int8_t *rssi, int8_t *noise)
{

	if (vap->iv_bss == NULL)		/* NB: shouldn't happen */
		return;
	vap->iv_ic->ic_node_getsignal(vap->iv_bss, rssi, noise);
	/* for non-station mode return avg'd rssi accounting */
	if (vap->iv_opmode != IEEE80211_M_STA)
		*rssi = ieee80211_getrssi(vap);
}