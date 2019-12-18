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
struct stainforeq {int /*<<< orphan*/  space; } ;
struct ieee80211_node {scalar_t__ ni_associd; TYPE_1__* ni_vap; } ;
struct TYPE_2__ {scalar_t__ iv_opmode; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ sta_space (struct ieee80211_node*,size_t*) ; 

__attribute__((used)) static void
get_sta_space(void *arg, struct ieee80211_node *ni)
{
	struct stainforeq *req = arg;
	size_t ielen;

	if (ni->ni_vap->iv_opmode == IEEE80211_M_HOSTAP &&
	    ni->ni_associd == 0)	/* only associated stations */
		return;
	req->space += sta_space(ni, &ielen);
}