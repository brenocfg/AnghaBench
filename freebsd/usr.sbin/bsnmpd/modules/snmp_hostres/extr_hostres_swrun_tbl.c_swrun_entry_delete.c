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
struct swrun_entry {struct swrun_entry* parameters; struct swrun_entry* path; struct swrun_entry* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct swrun_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct swrun_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  swrun_tbl ; 

__attribute__((used)) static void
swrun_entry_delete(struct swrun_entry *entry)
{

	assert(entry != NULL);

	TAILQ_REMOVE(&swrun_tbl, entry, link);

	free(entry->name);
	free(entry->path);
	free(entry->parameters);
	free(entry);
}