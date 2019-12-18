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
struct delegpt_addr {struct delegpt_addr* next_target; } ;
struct delegpt {struct delegpt_addr* target_list; } ;

/* Variables and functions */

size_t
delegpt_count_targets(struct delegpt* dp)
{
	struct delegpt_addr* a;
	size_t n = 0;
	for(a = dp->target_list; a; a = a->next_target)
		n++;
	return n;
}