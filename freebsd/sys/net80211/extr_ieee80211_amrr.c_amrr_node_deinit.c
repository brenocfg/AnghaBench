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
struct ieee80211_node {int /*<<< orphan*/  ni_rctls; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_RATECTL ; 

__attribute__((used)) static void
amrr_node_deinit(struct ieee80211_node *ni)
{
	IEEE80211_FREE(ni->ni_rctls, M_80211_RATECTL);
}