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
struct delegpt_addr {int attempts; struct delegpt_addr* next_result; struct delegpt_addr* next_target; } ;
struct delegpt {struct delegpt_addr* result_list; struct delegpt_addr* target_list; } ;

/* Variables and functions */
 int OUTBOUND_MSG_RETRY ; 

void iter_dec_attempts(struct delegpt* dp, int d)
{
	struct delegpt_addr* a;
	for(a=dp->target_list; a; a = a->next_target) {
		if(a->attempts >= OUTBOUND_MSG_RETRY) {
			/* add back to result list */
			a->next_result = dp->result_list;
			dp->result_list = a;
		}
		if(a->attempts > d)
			a->attempts -= d;
		else a->attempts = 0;
	}
}