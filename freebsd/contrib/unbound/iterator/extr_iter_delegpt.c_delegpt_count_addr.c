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
struct delegpt_addr {struct delegpt_addr* next_usable; struct delegpt_addr* next_result; struct delegpt_addr* next_target; } ;
struct delegpt {struct delegpt_addr* usable_list; struct delegpt_addr* result_list; struct delegpt_addr* target_list; } ;

/* Variables and functions */

void
delegpt_count_addr(struct delegpt* dp, size_t* numaddr, size_t* numres, 
	size_t* numavail)
{
	struct delegpt_addr* a;
	*numaddr = 0;
	*numres = 0;
	*numavail = 0;
	for(a = dp->target_list; a; a = a->next_target) {
		(*numaddr)++;
	}
	for(a = dp->result_list; a; a = a->next_result) {
		(*numres)++;
	}
	for(a = dp->usable_list; a; a = a->next_usable) {
		(*numavail)++;
	}
}