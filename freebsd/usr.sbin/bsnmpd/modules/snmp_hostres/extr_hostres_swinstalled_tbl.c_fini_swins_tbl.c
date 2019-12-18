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
struct swins_map_entry {struct swins_map_entry* name; struct swins_map_entry* entry; } ;

/* Variables and functions */
 struct swins_map_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct swins_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct swins_map_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  swins_map ; 
 int /*<<< orphan*/  swins_tbl ; 

void
fini_swins_tbl(void)
{
	struct swins_map_entry  *n1;

	while ((n1 = STAILQ_FIRST(&swins_map)) != NULL) {
		STAILQ_REMOVE_HEAD(&swins_map, link);
		if (n1->entry != NULL) {
			TAILQ_REMOVE(&swins_tbl, n1->entry, link);
			free(n1->entry->name);
			free(n1->entry);
		}
		free(n1->name);
		free(n1);
	}
	assert(TAILQ_EMPTY(&swins_tbl));
}