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
struct rtt_info {int rto; } ;

/* Variables and functions */
 int RTT_MAX_TIMEOUT ; 

void 
rtt_lost(struct rtt_info* rtt, int orig)
{
	/* exponential backoff */

	/* if a query succeeded and put down the rto meanwhile, ignore this */
	if(rtt->rto < orig)
		return;

	/* the original rto is doubled, not the current one to make sure
	 * that the values in the cache are not increased by lots of
	 * queries simultaneously as they time out at the same time */
	orig *= 2;
	if(rtt->rto <= orig) {
		rtt->rto = orig;
		if(rtt->rto > RTT_MAX_TIMEOUT)
			rtt->rto = RTT_MAX_TIMEOUT;
	}
}