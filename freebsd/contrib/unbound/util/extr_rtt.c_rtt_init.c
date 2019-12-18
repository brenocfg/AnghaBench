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
struct rtt_info {int rttvar; int /*<<< orphan*/  rto; scalar_t__ srtt; } ;

/* Variables and functions */
 int UNKNOWN_SERVER_NICENESS ; 
 int /*<<< orphan*/  calc_rto (struct rtt_info*) ; 

void 
rtt_init(struct rtt_info* rtt)
{
	rtt->srtt = 0;
	rtt->rttvar = UNKNOWN_SERVER_NICENESS/4;
	rtt->rto = calc_rto(rtt);
	/* default value from the book is 0 + 4*0.75 = 3 seconds */
	/* first RTO is 0 + 4*0.094 = 0.376 seconds */
}