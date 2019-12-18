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
struct unwind_table_entry {int region_start; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_unwind_table_entry(const void *a, const void *b)
{
	return ((const struct unwind_table_entry *)a)->region_start
	     - ((const struct unwind_table_entry *)b)->region_start;
}