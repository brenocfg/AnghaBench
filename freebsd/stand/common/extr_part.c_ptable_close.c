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
struct ptable {int /*<<< orphan*/  entries; } ;
struct pentry {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ptable* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,struct ptable*) ; 
 int /*<<< orphan*/  free (struct ptable*) ; 

void
ptable_close(struct ptable *table)
{
	struct pentry *entry;

	if (table == NULL)
		return;

	while (!STAILQ_EMPTY(&table->entries)) {
		entry = STAILQ_FIRST(&table->entries);
		STAILQ_REMOVE_HEAD(&table->entries, entry);
		free(entry);
	}
	free(table);
}