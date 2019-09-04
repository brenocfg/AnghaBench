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
struct ref_entry {int dummy; } ;
struct ref_dir {int nr; int sorted; struct ref_entry** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOVE_ARRAY (struct ref_entry**,struct ref_entry**,int) ; 
 struct ref_dir* find_containing_dir (struct ref_dir*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_ref_entry (struct ref_entry*) ; 
 int search_ref_dir (struct ref_dir*,char const*,int) ; 
 int strlen (char const*) ; 
 char* xmemdupz (char const*,int) ; 

int remove_entry_from_dir(struct ref_dir *dir, const char *refname)
{
	int refname_len = strlen(refname);
	int entry_index;
	struct ref_entry *entry;
	int is_dir = refname[refname_len - 1] == '/';
	if (is_dir) {
		/*
		 * refname represents a reference directory.  Remove
		 * the trailing slash; otherwise we will get the
		 * directory *representing* refname rather than the
		 * one *containing* it.
		 */
		char *dirname = xmemdupz(refname, refname_len - 1);
		dir = find_containing_dir(dir, dirname, 0);
		free(dirname);
	} else {
		dir = find_containing_dir(dir, refname, 0);
	}
	if (!dir)
		return -1;
	entry_index = search_ref_dir(dir, refname, refname_len);
	if (entry_index == -1)
		return -1;
	entry = dir->entries[entry_index];

	MOVE_ARRAY(&dir->entries[entry_index],
		   &dir->entries[entry_index + 1], dir->nr - entry_index - 1);
	dir->nr--;
	if (dir->sorted > entry_index)
		dir->sorted--;
	free_ref_entry(entry);
	return dir->nr;
}