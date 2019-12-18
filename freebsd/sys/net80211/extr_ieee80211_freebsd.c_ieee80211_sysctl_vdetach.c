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
struct ieee80211vap {int /*<<< orphan*/ * iv_sysctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

void
ieee80211_sysctl_vdetach(struct ieee80211vap *vap)
{

	if (vap->iv_sysctl != NULL) {
		sysctl_ctx_free(vap->iv_sysctl);
		IEEE80211_FREE(vap->iv_sysctl, M_DEVBUF);
		vap->iv_sysctl = NULL;
	}
}