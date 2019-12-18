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
struct mwl_hal_vap {int dummy; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {struct mwl_hal_vap* mv_hvap; } ;

/* Variables and functions */
 TYPE_1__* MWL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mwl_getapmode (struct ieee80211vap*,struct ieee80211_channel*) ; 
 int mwl_hal_setapmode (struct mwl_hal_vap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwl_setapmode(struct ieee80211vap *vap, struct ieee80211_channel *chan)
{
	struct mwl_hal_vap *hvap = MWL_VAP(vap)->mv_hvap;
	return mwl_hal_setapmode(hvap, mwl_getapmode(vap, chan));
}