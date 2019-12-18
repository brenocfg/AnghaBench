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
struct ieee80211_node {scalar_t__ ni_mlhcnt; } ;

/* Variables and functions */

__attribute__((used)) static void
mesh_peer_backoff_cb(void *arg)
{
	struct ieee80211_node *ni = (struct ieee80211_node *)arg;

	/* After backoff timeout, try to peer automatically again. */
	ni->ni_mlhcnt = 0;
}