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
struct ieee80211com {int /*<<< orphan*/ * ic_countryie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE_IE ; 

void
ieee80211_regdomain_detach(struct ieee80211com *ic)
{
	if (ic->ic_countryie != NULL) {
		IEEE80211_FREE(ic->ic_countryie, M_80211_NODE_IE);
		ic->ic_countryie = NULL;
	}
}