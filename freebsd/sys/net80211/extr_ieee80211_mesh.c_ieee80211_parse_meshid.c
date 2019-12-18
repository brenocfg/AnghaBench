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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_node {int /*<<< orphan*/  ni_meshid; int /*<<< orphan*/  ni_meshidlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 

void
ieee80211_parse_meshid(struct ieee80211_node *ni, const uint8_t *ie)
{
	ni->ni_meshidlen = ie[1];
	memcpy(ni->ni_meshid, ie + 2, ie[1]);
}