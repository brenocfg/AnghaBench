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
struct delegpt_ns {int resolved; scalar_t__ got4; struct delegpt_ns* next; } ;
struct delegpt {struct delegpt_ns* nslist; } ;

/* Variables and functions */

void delegpt_no_ipv6(struct delegpt* dp)
{
	struct delegpt_ns* ns;
	for(ns = dp->nslist; ns; ns = ns->next) {
		/* no ipv6, so only ipv4 is enough to resolve a nameserver */
		if(ns->got4)
			ns->resolved = 1;
	}
}