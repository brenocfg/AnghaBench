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
struct fadump_mrange_info {scalar_t__ max_mem_ranges; scalar_t__ mem_ranges_sz; int /*<<< orphan*/ * mem_ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fadump_free_mem_ranges(struct fadump_mrange_info *mrange_info)
{
	kfree(mrange_info->mem_ranges);
	mrange_info->mem_ranges = NULL;
	mrange_info->mem_ranges_sz = 0;
	mrange_info->max_mem_ranges = 0;
}