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
struct sbuf {int dummy; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_macaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_ratectl_node_stats (struct ieee80211_node*,struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
ieee80211_ratectl_sysctl_stats_node_iter(void *arg, struct ieee80211_node *ni)
{

	struct sbuf *sb = (struct sbuf *) arg;
	sbuf_printf(sb, "MAC: %6D\n", ni->ni_macaddr, ":");
	ieee80211_ratectl_node_stats(ni, sb);
	sbuf_printf(sb, "\n");
}