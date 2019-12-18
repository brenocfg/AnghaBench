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
struct ieee80211vap {int /*<<< orphan*/  iv_rs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_80211_RATECTL ; 
 scalar_t__ nrefs ; 

__attribute__((used)) static void
amrr_deinit(struct ieee80211vap *vap)
{
	IEEE80211_FREE(vap->iv_rs, M_80211_RATECTL);
	KASSERT(nrefs > 0, ("imbalanced attach/detach"));
	nrefs--;		/* XXX locking */
}