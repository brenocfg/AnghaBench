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
struct ieee80211_scanparams {int /*<<< orphan*/  meshid; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_parse_meshid (struct ieee80211_node*,int /*<<< orphan*/ ) ; 

void
ieee80211_mesh_init_neighbor(struct ieee80211_node *ni,
	const struct ieee80211_frame *wh,
	const struct ieee80211_scanparams *sp)
{
	ieee80211_parse_meshid(ni, sp->meshid);
}