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
typedef  int uint8_t ;
struct ieee80211vap {TYPE_2__* iv_ic; TYPE_1__* iv_bss; } ;
struct ieee80211_channel {scalar_t__ ic_maxregpower; } ;
typedef  scalar_t__ int8_t ;
struct TYPE_4__ {int ic_txpowlimit; } ;
struct TYPE_3__ {struct ieee80211_channel* ni_chan; } ;

/* Variables and functions */
 int IEEE80211_ELEMID_PWRCNSTR ; 

__attribute__((used)) static uint8_t *
ieee80211_add_powerconstraint(uint8_t *frm, struct ieee80211vap *vap)
{
	const struct ieee80211_channel *c = vap->iv_bss->ni_chan;
	/* XXX per-vap tx power limit? */
	int8_t limit = vap->iv_ic->ic_txpowlimit / 2;

	frm[0] = IEEE80211_ELEMID_PWRCNSTR;
	frm[1] = 1;
	frm[2] = c->ic_maxregpower > limit ?  c->ic_maxregpower - limit : 0;
	return frm + 3;
}