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
struct ieee80211_rssadapt_node {int ra_pktrate; int ra_nfail; int ra_nok; int /*<<< orphan*/  ra_raise_interval; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  msecs_to_ticks (long) ; 

__attribute__((used)) static void
rssadapt_updatestats(struct ieee80211_rssadapt_node *ra)
{
	long interval;

	ra->ra_pktrate = (ra->ra_pktrate + 10*(ra->ra_nfail + ra->ra_nok))/2;
	ra->ra_nfail = ra->ra_nok = 0;

	/*
	 * A node is eligible for its rate to be raised every 1/10 to 10
	 * seconds, more eligible in proportion to recent packet rates.
	 */
	interval = MAX(10*1000, 10*1000 / MAX(1, 10 * ra->ra_pktrate));
	ra->ra_raise_interval = msecs_to_ticks(interval);
}