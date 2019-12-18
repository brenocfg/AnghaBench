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
struct object_id {int dummy; } ;
struct merge_parents {int nr; TYPE_1__* item; int /*<<< orphan*/  alloc; } ;
struct TYPE_2__ {scalar_t__ used; int /*<<< orphan*/  commit; int /*<<< orphan*/  given; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ find_merge_parent (struct merge_parents*,struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 

__attribute__((used)) static void add_merge_parent(struct merge_parents *table,
			     struct object_id *given,
			     struct object_id *commit)
{
	if (table->nr && find_merge_parent(table, given, commit))
		return;
	ALLOC_GROW(table->item, table->nr + 1, table->alloc);
	oidcpy(&table->item[table->nr].given, given);
	oidcpy(&table->item[table->nr].commit, commit);
	table->item[table->nr].used = 0;
	table->nr++;
}