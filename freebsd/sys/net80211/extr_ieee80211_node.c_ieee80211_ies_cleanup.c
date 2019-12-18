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
struct ieee80211_ies {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE_IE ; 

void
ieee80211_ies_cleanup(struct ieee80211_ies *ies)
{
	if (ies->data != NULL)
		IEEE80211_FREE(ies->data, M_80211_NODE_IE);
}