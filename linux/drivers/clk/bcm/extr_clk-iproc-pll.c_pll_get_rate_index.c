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
struct iproc_pll {int num_vco_entries; TYPE_1__* vco_param; } ;
struct TYPE_2__ {unsigned int rate; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int pll_get_rate_index(struct iproc_pll *pll, unsigned int target_rate)
{
	int i;

	for (i = 0; i < pll->num_vco_entries; i++)
		if (target_rate == pll->vco_param[i].rate)
			break;

	if (i >= pll->num_vco_entries)
		return -EINVAL;

	return i;
}