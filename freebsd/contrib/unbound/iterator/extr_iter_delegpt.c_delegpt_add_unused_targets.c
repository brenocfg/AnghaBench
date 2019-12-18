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
struct delegpt_addr {struct delegpt_addr* next_usable; struct delegpt_addr* next_result; } ;
struct delegpt {struct delegpt_addr* result_list; struct delegpt_addr* usable_list; } ;

/* Variables and functions */

void 
delegpt_add_unused_targets(struct delegpt* dp)
{
	struct delegpt_addr* usa = dp->usable_list;
	dp->usable_list = NULL;
	while(usa) {
		usa->next_result = dp->result_list;
		dp->result_list = usa;
		usa = usa->next_usable;
	}
}