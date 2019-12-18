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
struct rtt_info {scalar_t__ rto; int srtt; int rttvar; } ;

/* Variables and functions */
 scalar_t__ calc_rto (struct rtt_info const*) ; 

int 
rtt_unclamped(const struct rtt_info* rtt)
{
	if(calc_rto(rtt) != rtt->rto) {
		/* timeout fallback has happened */
		return rtt->rto;
	}
	/* return unclamped value */
	return rtt->srtt + 4*rtt->rttvar;
}