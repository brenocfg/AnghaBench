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
struct ieee80211_channel {int ic_ieee; int ic_freq; int ic_maxpower; int ic_maxregpower; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

__attribute__((used)) static void
print_txpow(const struct ieee80211_channel *c)
{
	printf("Channel %3u : %u MHz %3.1f reg %2d  ",
	    c->ic_ieee, c->ic_freq,
	    c->ic_maxpower/2., c->ic_maxregpower);
}