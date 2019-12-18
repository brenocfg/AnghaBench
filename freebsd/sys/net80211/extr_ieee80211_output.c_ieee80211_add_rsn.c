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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211vap {int iv_flags; int /*<<< orphan*/ * iv_rsn_ie; } ;

/* Variables and functions */
 int IEEE80211_F_WPA2 ; 
 int /*<<< orphan*/ * add_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint8_t *
ieee80211_add_rsn(uint8_t *frm, const struct ieee80211vap *vap)
{
	if (vap->iv_flags & IEEE80211_F_WPA2 && vap->iv_rsn_ie != NULL)
		return (add_ie(frm, vap->iv_rsn_ie));
	else {
		/* XXX else complain? */
		return (frm);
	}
}