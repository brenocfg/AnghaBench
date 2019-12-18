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
struct scpi_opp {unsigned long freq; } ;
struct scpi_clk {TYPE_1__* info; } ;
struct TYPE_2__ {int count; struct scpi_opp* opps; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int __scpi_find_dvfs_index(struct scpi_clk *clk, unsigned long rate)
{
	int idx, max_opp = clk->info->count;
	const struct scpi_opp *opp = clk->info->opps;

	for (idx = 0; idx < max_opp; idx++, opp++)
		if (opp->freq == rate)
			return idx;
	return -EINVAL;
}