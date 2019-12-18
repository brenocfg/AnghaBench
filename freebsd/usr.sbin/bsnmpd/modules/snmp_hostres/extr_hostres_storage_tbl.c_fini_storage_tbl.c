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
struct storage_map_entry {struct storage_map_entry* a_name; struct storage_map_entry* entry; struct storage_map_entry* descr; } ;

/* Variables and functions */
 struct storage_map_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct storage_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct storage_map_entry*) ; 
 struct storage_map_entry* fs_buf ; 
 scalar_t__ fs_buf_count ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  storage_map ; 
 int /*<<< orphan*/  storage_tbl ; 
 struct storage_map_entry* swap_devs ; 
 scalar_t__ swap_devs_len ; 

void
fini_storage_tbl(void)
{
	struct storage_map_entry *n1;

	if (swap_devs != NULL) {
		free(swap_devs);
		swap_devs = NULL;
	}
	swap_devs_len = 0;

	if (fs_buf != NULL) {
		free(fs_buf);
		fs_buf = NULL;
	}
	fs_buf_count = 0;

	while ((n1 = STAILQ_FIRST(&storage_map)) != NULL) {
		STAILQ_REMOVE_HEAD(&storage_map, link);
		if (n1->entry != NULL) {
			TAILQ_REMOVE(&storage_tbl, n1->entry, link);
			free(n1->entry->descr);
			free(n1->entry);
		}
		free(n1->a_name);
		free(n1);
	}
	assert(TAILQ_EMPTY(&storage_tbl));
}