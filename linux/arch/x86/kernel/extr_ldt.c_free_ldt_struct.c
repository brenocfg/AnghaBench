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
struct ldt_struct {int nr_entries; scalar_t__ entries; } ;

/* Variables and functions */
 int LDT_ENTRY_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct ldt_struct*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  paravirt_free_ldt (scalar_t__,int) ; 
 int /*<<< orphan*/  vfree_atomic (scalar_t__) ; 

__attribute__((used)) static void free_ldt_struct(struct ldt_struct *ldt)
{
	if (likely(!ldt))
		return;

	paravirt_free_ldt(ldt->entries, ldt->nr_entries);
	if (ldt->nr_entries * LDT_ENTRY_SIZE > PAGE_SIZE)
		vfree_atomic(ldt->entries);
	else
		free_page((unsigned long)ldt->entries);
	kfree(ldt);
}