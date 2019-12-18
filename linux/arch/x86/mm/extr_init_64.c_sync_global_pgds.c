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
 scalar_t__ pgtable_l5_enabled () ; 
 int /*<<< orphan*/  sync_global_pgds_l4 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  sync_global_pgds_l5 (unsigned long,unsigned long) ; 

void sync_global_pgds(unsigned long start, unsigned long end)
{
	if (pgtable_l5_enabled())
		sync_global_pgds_l5(start, end);
	else
		sync_global_pgds_l4(start, end);
}