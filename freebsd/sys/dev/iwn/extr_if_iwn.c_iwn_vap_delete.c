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
struct iwn_vap {int dummy; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 struct iwn_vap* IWN_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  M_80211_VAP ; 
 int /*<<< orphan*/  free (struct iwn_vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ratectl_deinit (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_vap_detach (struct ieee80211vap*) ; 

__attribute__((used)) static void
iwn_vap_delete(struct ieee80211vap *vap)
{
	struct iwn_vap *ivp = IWN_VAP(vap);

	ieee80211_ratectl_deinit(vap);
	ieee80211_vap_detach(vap);
	free(ivp, M_80211_VAP);
}