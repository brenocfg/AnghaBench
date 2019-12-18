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
struct fs_map_entry {struct fs_map_entry* a_name; struct fs_map_entry* entry; struct fs_map_entry* remoteMountPoint; struct fs_map_entry* mountPoint; } ;

/* Variables and functions */
 struct fs_map_entry* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct fs_map_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fs_map_entry*) ; 
 int /*<<< orphan*/  fs_map ; 
 int /*<<< orphan*/  fs_tbl ; 
 int /*<<< orphan*/  link ; 

void
fini_fs_tbl(void)
{
	struct fs_map_entry *n1;

     	while ((n1 = STAILQ_FIRST(&fs_map)) != NULL) {
		STAILQ_REMOVE_HEAD(&fs_map, link);
		if (n1->entry != NULL) {
			TAILQ_REMOVE(&fs_tbl, n1->entry, link);
			free(n1->entry->mountPoint);
			free(n1->entry->remoteMountPoint);
			free(n1->entry);
		}
		free(n1->a_name);
		free(n1);
     	}
	assert(TAILQ_EMPTY(&fs_tbl));
}