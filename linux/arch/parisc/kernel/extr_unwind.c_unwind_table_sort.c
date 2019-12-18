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
struct unwind_table_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_unwind_table_entry ; 
 int /*<<< orphan*/  sort (struct unwind_table_entry*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unwind_table_sort(struct unwind_table_entry *start,
		  struct unwind_table_entry *finish)
{
	sort(start, finish - start, sizeof(struct unwind_table_entry),
	     cmp_unwind_table_entry, NULL);
}