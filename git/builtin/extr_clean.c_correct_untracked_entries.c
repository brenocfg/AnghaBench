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
struct dir_struct {int nr; int ignored_nr; struct dir_entry** entries; struct dir_entry** ignored; } ;
struct dir_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_dir_entry_contains (struct dir_entry*,struct dir_entry*) ; 
 scalar_t__ cmp_dir_entry (struct dir_entry**,struct dir_entry**) ; 
 int /*<<< orphan*/  free (struct dir_entry*) ; 

__attribute__((used)) static void correct_untracked_entries(struct dir_struct *dir)
{
	int src, dst, ign;

	for (src = dst = ign = 0; src < dir->nr; src++) {
		/* skip paths in ignored[] that cannot be inside entries[src] */
		while (ign < dir->ignored_nr &&
		       0 <= cmp_dir_entry(&dir->entries[src], &dir->ignored[ign]))
			ign++;

		if (ign < dir->ignored_nr &&
		    check_dir_entry_contains(dir->entries[src], dir->ignored[ign])) {
			/* entries[src] contains an ignored path, so we drop it */
			free(dir->entries[src]);
		} else {
			struct dir_entry *ent = dir->entries[src++];

			/* entries[src] does not contain an ignored path, so we keep it */
			dir->entries[dst++] = ent;

			/* then discard paths in entries[] contained inside entries[src] */
			while (src < dir->nr &&
			       check_dir_entry_contains(ent, dir->entries[src]))
				free(dir->entries[src++]);

			/* compensate for the outer loop's loop control */
			src--;
		}
	}
	dir->nr = dst;
}