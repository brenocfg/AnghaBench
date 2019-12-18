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
 int /*<<< orphan*/  CRST_ALLOC_ORDER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crst_table_init (unsigned long*,unsigned long) ; 

__attribute__((used)) static unsigned long base_crst_alloc(unsigned long val)
{
	unsigned long table;

	table =	 __get_free_pages(GFP_KERNEL, CRST_ALLOC_ORDER);
	if (table)
		crst_table_init((unsigned long *)table, val);
	return table;
}