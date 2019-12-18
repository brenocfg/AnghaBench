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
struct unwind_table {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_USER ; 
 struct unwind_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unwind_lock ; 
 int /*<<< orphan*/  unwind_table_init (struct unwind_table*,char const*,unsigned long,unsigned long,void*,void*) ; 
 int /*<<< orphan*/  unwind_table_sort (struct unwind_table_entry*,struct unwind_table_entry*) ; 
 int /*<<< orphan*/  unwind_tables ; 

struct unwind_table *
unwind_table_add(const char *name, unsigned long base_addr, 
		 unsigned long gp,
                 void *start, void *end)
{
	struct unwind_table *table;
	unsigned long flags;
	struct unwind_table_entry *s = (struct unwind_table_entry *)start;
	struct unwind_table_entry *e = (struct unwind_table_entry *)end;

	unwind_table_sort(s, e);

	table = kmalloc(sizeof(struct unwind_table), GFP_USER);
	if (table == NULL)
		return NULL;
	unwind_table_init(table, name, base_addr, gp, start, end);
	spin_lock_irqsave(&unwind_lock, flags);
	list_add_tail(&table->list, &unwind_tables);
	spin_unlock_irqrestore(&unwind_lock, flags);

	return table;
}