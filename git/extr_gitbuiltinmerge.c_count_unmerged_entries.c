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

/* Variables and functions */
 int /*<<< orphan*/ * active_cache ; 
 int active_nr ; 
 scalar_t__ ce_stage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_unmerged_entries(void)
{
	int i, ret = 0;

	for (i = 0; i < active_nr; i++)
		if (ce_stage(active_cache[i]))
			ret++;

	return ret;
}