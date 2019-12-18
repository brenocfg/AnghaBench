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
struct ieee80211_channel {int ic_minpower; int ic_maxpower; int ic_maxregpower; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_chaninfo (struct ieee80211_channel const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_txpow_verbose(const struct ieee80211_channel *c)
{
	print_chaninfo(c, 1);
	printf("min %4.1f dBm  max %3.1f dBm  reg %2d dBm",
	    c->ic_minpower/2., c->ic_maxpower/2., c->ic_maxregpower);
	/* indicate where regulatory cap limits power use */
	if (c->ic_maxpower > 2*c->ic_maxregpower)
		printf(" <");
}