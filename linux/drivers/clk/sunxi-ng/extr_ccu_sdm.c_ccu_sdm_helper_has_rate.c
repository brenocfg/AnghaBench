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
struct ccu_sdm_internal {unsigned int table_size; TYPE_1__* table; } ;
struct ccu_common {int features; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int CCU_FEATURE_SIGMA_DELTA_MOD ; 

bool ccu_sdm_helper_has_rate(struct ccu_common *common,
			     struct ccu_sdm_internal *sdm,
			     unsigned long rate)
{
	unsigned int i;

	if (!(common->features & CCU_FEATURE_SIGMA_DELTA_MOD))
		return false;

	for (i = 0; i < sdm->table_size; i++)
		if (sdm->table[i].rate == rate)
			return true;

	return false;
}