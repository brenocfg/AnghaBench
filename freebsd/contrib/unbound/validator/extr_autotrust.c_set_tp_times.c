#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct trust_anchor {TYPE_1__* autr; } ;
struct TYPE_2__ {int query_interval; int retry_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  autr_permit_small_holddown ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void
set_tp_times(struct trust_anchor* tp, time_t rrsig_exp_interval, 
	time_t origttl, int* changed)
{
	time_t x, qi = tp->autr->query_interval, rt = tp->autr->retry_time;
	
	/* x = MIN(15days, ttl/2, expire/2) */
	x = 15 * 24 * 3600;
	if(origttl/2 < x)
		x = origttl/2;
	if(rrsig_exp_interval/2 < x)
		x = rrsig_exp_interval/2;
	/* MAX(1hr, x) */
	if(!autr_permit_small_holddown) {
		if(x < 3600)
			tp->autr->query_interval = 3600;
		else	tp->autr->query_interval = x;
	}	else    tp->autr->query_interval = x;

	/* x= MIN(1day, ttl/10, expire/10) */
	x = 24 * 3600;
	if(origttl/10 < x)
		x = origttl/10;
	if(rrsig_exp_interval/10 < x)
		x = rrsig_exp_interval/10;
	/* MAX(1hr, x) */
	if(!autr_permit_small_holddown) {
		if(x < 3600)
			tp->autr->retry_time = 3600;
		else	tp->autr->retry_time = x;
	}	else    tp->autr->retry_time = x;

	if(qi != tp->autr->query_interval || rt != tp->autr->retry_time) {
		*changed = 1;
		verbose(VERB_ALGO, "orig_ttl is %d", (int)origttl);
		verbose(VERB_ALGO, "rrsig_exp_interval is %d", 
			(int)rrsig_exp_interval);
		verbose(VERB_ALGO, "query_interval: %d, retry_time: %d",
			(int)tp->autr->query_interval, 
			(int)tp->autr->retry_time);
	}
}