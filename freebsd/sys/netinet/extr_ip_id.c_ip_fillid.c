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
typedef  int uint64_t ;
struct ip {int ip_off; int ip_id; } ;

/* Variables and functions */
 int IP_DF ; 
 scalar_t__ V_ip_do_randomid ; 
 int /*<<< orphan*/  V_ip_id ; 
 scalar_t__ V_ip_rfc6864 ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int htons (int) ; 
 int ip_randomid () ; 
 scalar_t__ zpcpu_get (int /*<<< orphan*/ ) ; 

void
ip_fillid(struct ip *ip)
{

	/*
	 * Per RFC6864 Section 4
	 *
	 * o  Atomic datagrams: (DF==1) && (MF==0) && (frag_offset==0)
	 * o  Non-atomic datagrams: (DF==0) || (MF==1) || (frag_offset>0)
	 */
	if (V_ip_rfc6864 && (ip->ip_off & htons(IP_DF)) == htons(IP_DF))
		ip->ip_id = 0;
	else if (V_ip_do_randomid)
		ip->ip_id = ip_randomid();
	else {
		counter_u64_add(V_ip_id, 1);
		/*
		 * There are two issues about this trick, to be kept in mind.
		 * 1) We can migrate between counter_u64_add() and next
		 *    line, and grab counter from other CPU, resulting in too
		 *    quick ID reuse. This is tolerable in our particular case,
		 *    since probability of such event is much lower then reuse
		 *    of ID due to legitimate overflow, that at modern Internet
		 *    speeds happens all the time.
		 * 2) We are relying on the fact that counter(9) is based on
		 *    UMA_ZONE_PCPU uma(9) zone. We also take only last
		 *    sixteen bits of a counter, so we don't care about the
		 *    fact that machines with 32-bit word update their counters
		 *    not atomically.
		 */
		ip->ip_id = htons((*(uint64_t *)zpcpu_get(V_ip_id)) & 0xffff);
	}
}