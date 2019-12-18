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
typedef  scalar_t__ u32 ;
struct ve_spc_opp {scalar_t__ freq; } ;
struct TYPE_2__ {int* num_opps; struct ve_spc_opp** opps; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* info ; 

__attribute__((used)) static int ve_spc_find_performance_index(int cluster, u32 freq)
{
	int idx, max_opp = info->num_opps[cluster];
	struct ve_spc_opp *opps = info->opps[cluster];

	for (idx = 0; idx < max_opp; idx++, opps++)
		if (opps->freq == freq)
			break;
	return (idx == max_opp) ? -EINVAL : idx;
}