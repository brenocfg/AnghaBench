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
struct rtt_info {int srtt; int rttvar; } ;

/* Variables and functions */
 int RTT_MAX_TIMEOUT ; 
 int RTT_MIN_TIMEOUT ; 

__attribute__((used)) static int
calc_rto(const struct rtt_info* rtt)
{
	/* From Stevens, Unix Network Programming, Vol1, 3rd ed., p.598 */
	int rto = rtt->srtt + 4*rtt->rttvar;
	if(rto < RTT_MIN_TIMEOUT)
		rto = RTT_MIN_TIMEOUT;
	if(rto > RTT_MAX_TIMEOUT)
		rto = RTT_MAX_TIMEOUT;
	return rto;
}