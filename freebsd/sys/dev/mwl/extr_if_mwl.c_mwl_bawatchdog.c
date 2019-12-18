#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_node {int dummy; } ;
struct TYPE_3__ {struct ieee80211_node** data; } ;
typedef  TYPE_1__ MWL_HAL_BASTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_REASON_UNSPECIFIED ; 
 int /*<<< orphan*/  ieee80211_ampdu_stop (struct ieee80211_node*,struct ieee80211_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl_bawatchdog(const MWL_HAL_BASTREAM *sp)
{
	struct ieee80211_node *ni = sp->data[0];

	/* send DELBA and drop the stream */
	ieee80211_ampdu_stop(ni, sp->data[1], IEEE80211_REASON_UNSPECIFIED);
}