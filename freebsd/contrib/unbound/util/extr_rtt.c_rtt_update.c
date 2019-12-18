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
struct rtt_info {int srtt; int rttvar; int /*<<< orphan*/  rto; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_rto (struct rtt_info*) ; 

void 
rtt_update(struct rtt_info* rtt, int ms)
{
	int delta = ms - rtt->srtt;
	rtt->srtt += delta / 8; /* g = 1/8 */
	if(delta < 0)
		delta = -delta; /* |delta| */
	rtt->rttvar += (delta - rtt->rttvar) / 4; /* h = 1/4 */
	rtt->rto = calc_rto(rtt);
}