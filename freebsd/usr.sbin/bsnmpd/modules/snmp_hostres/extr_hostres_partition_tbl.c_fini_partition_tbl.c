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
struct partition_map_entry {struct partition_map_entry* id; struct partition_map_entry* entry; struct partition_map_entry* label; } ;

/* Variables and functions */
 struct partition_map_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct partition_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct partition_map_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  partition_map ; 
 int /*<<< orphan*/  partition_tbl ; 

void
fini_partition_tbl(void)
{
	struct partition_map_entry *m;

	while ((m = STAILQ_FIRST(&partition_map)) != NULL) {
		STAILQ_REMOVE_HEAD(&partition_map, link);
		if(m->entry != NULL) {
			TAILQ_REMOVE(&partition_tbl, m->entry, link);
			free(m->entry->id);
			free(m->entry->label);
			free(m->entry);
		}
		free(m->id);
		free(m);
	}
	assert(TAILQ_EMPTY(&partition_tbl));
}