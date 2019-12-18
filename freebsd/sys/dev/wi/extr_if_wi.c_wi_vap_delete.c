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
struct wi_vap {int dummy; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_80211_VAP ; 
 struct wi_vap* WI_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  free (struct wi_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 

__attribute__((used)) static void
wi_vap_delete(struct ieee80211vap *vap)
{
	struct wi_vap *wvp = WI_VAP(vap);

	ieee80211_vap_detach(vap);
	free(wvp, M_80211_VAP);
}